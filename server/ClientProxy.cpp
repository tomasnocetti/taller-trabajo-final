#include "ClientProxy.h"

#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>

#include "../common/common_utils.h"

ClientProxy::ClientProxy(InstructionBQ &instructionQueue, Socket&& socket):
  running(true),
  authenticated(false),
  playerId(0),
  readProxy(*this),
  writeProxy(*this),
  instructionQueue(instructionQueue),
  acceptedSocket(std::move(socket)) {}

void ClientProxy::start(){
  readProxy.start();
  writeProxy.start();
}

void ClientProxy::setPlayerId(size_t id) {
  playerId = id;
  authenticated = true;
}

ResponseBQ& ClientProxy::getUpdateBQ() {
  return responseBQ;
}

void ClientProxy::stop(){
  running = false;
  responseBQ.close();
  acceptedSocket.close();
}

bool ClientProxy::isClose(){
  return !running;
}

void ClientProxy::join(){
  writeProxy.join();
  readProxy.join();
}

ClientProxy::~ClientProxy(){}

ClientProxyRead::ClientProxyRead(ClientProxy& client) :
  client(client) {}

void ClientProxyRead::run(){
  try{
    while (client.running){
      std::string buffer;
      InstructionData i;
      bool success = getRawInstruction(buffer);
      if (!success) {
        std::cout << "CERRANDO!" << std::endl;
        client.running = false;
        i = {CLOSE_SERVER, {}};
      } else {
        i = getInstruction(buffer);
      }

      /** HANDLE **/
      if (!client.authenticated) {
        handleNonAuthInstruction(i);
      } else {
        handleAuthInstruction(i);
      }
    }
  } catch(const std::exception& e) {
    std::cout << "ERROR CLIENT PROXY READ: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CLIENT PROXY READ" << std::endl;
  }
}

bool ClientProxyRead::getRawInstruction(std::string& buffer) {
  uint32_t sizeInstruction = 0;
  bool success = client.acceptedSocket.receive((char*) &sizeInstruction, 4);
  if (!success) return false;

  sizeInstruction = from_big_end<uint32_t>(sizeInstruction);

  std::vector<char> res_message(sizeInstruction);

  success = client.acceptedSocket.receive(res_message.data(), sizeInstruction);
  if (!success) return false;

  buffer = std::string(res_message.begin(), res_message.end());
  return true;
}

InstructionData ClientProxyRead::getInstruction(std::string& instruction) {
  msgpack::object_handle oh =
        msgpack::unpack(instruction.data(), instruction.size());
  msgpack::object deserialized = oh.get();
  InstructionData instructionData = deserialized.as<InstructionData>();

  return instructionData;
}

void ClientProxyRead::handleAuthInstruction(
  InstructionData& instruction) {
  ActionTypeT action = instruction.action;
  std::unique_ptr<Instruction> i;

  switch (action) {
    case MOVE:
      i = std::unique_ptr<Instruction>(new MoveInstruction(
        client.playerId,
        instruction.params[0].value,
        instruction.params[1].value));
      client.instructionQueue.push(std::move(i));
      break;
    case BUY:
      i = std::unique_ptr<Instruction>(new BuyInstruction(
        client.playerId, instruction.params[0].value));
      client.instructionQueue.push(std::move(i));
      break;
    case DEPOSIT_GOLD:
      break;
    case DEPOSIT_ITEM:
      break;
    case ATTACK:
      i = std::unique_ptr<Instruction>(new AttackInstrucion(
        client.playerId,
        instruction.params[0].value,
        instruction.params[1].value));
      client.instructionQueue.push(std::move(i));
      break;
    case CLOSE_SERVER:
      client.running = false;
      i = std::unique_ptr<Instruction>(new CloseInstruction(client.playerId));
      client.instructionQueue.push(std::move(i));
      break;
    case LOAD_PLAYER:
      break;
    case AUTHENTICATE:
      i = std::unique_ptr<Instruction>(
        new AuthInstruction(client, instruction.params[0].value));
      client.instructionQueue.push(std::move(i));
      break;
    case STOP_MOVEMENT:
      i = std::unique_ptr<Instruction>(new StopMovementInstruction(
        client.playerId));
      client.instructionQueue.push(std::move(i));
      break;
    case EQUIP:
      i = std::unique_ptr<Instruction>(new EquipInstruction(
        client.playerId, instruction.params[0].value));
      client.instructionQueue.push(std::move(i));
      break;
    case RESURRECT:
      i = std::unique_ptr<Instruction>(new ResurrectInstrucion(
        client.playerId));
      client.instructionQueue.push(std::move(i));
      break;
    case MEDITATE:
      i = std::unique_ptr<Instruction>(new MeditateInstruction(
        client.playerId));
      client.instructionQueue.push(std::move(i));
      break;
    case THROW_OBJECT:
      i = std::unique_ptr<Instruction>(new ThrowObjInstruction(
        client.playerId, instruction.params[0].value));
      client.instructionQueue.push(std::move(i));      
      break;
    case PICK_UP:
      i = std::unique_ptr<Instruction>(new PickUpInstruction(
        client.playerId));
      client.instructionQueue.push(std::move(i));      
      break; 
    case LIST:
      i = std::unique_ptr<Instruction>(new ListInstruction(
        client.playerId));
      client.instructionQueue.push(std::move(i));      
      break; 
    default:
      std::cout << "El jugador quiere realizar otra accion. " << std::endl;
      break;
  }
}

void ClientProxyRead::handleNonAuthInstruction(
  InstructionData& instruction) {
  ActionTypeT action = instruction.action;
  std::unique_ptr<Instruction> i;

  switch (action) {
    case AUTHENTICATE:
      i = std::unique_ptr<Instruction>(
        new AuthInstruction(client, instruction.params[0].value));
      client.instructionQueue.push(std::move(i));
      break;
    default:
      std::cout << "El jugador quiere realizar otra accion. " << std::endl;
      break;
  }
}

ClientProxyWrite::ClientProxyWrite(ClientProxy& client) :
  client(client) {}

void ClientProxyWrite::run(){
  try{
    while (client.running){
      std::unique_ptr<Response> r;
      bool success = client.responseBQ.try_front_pop(r);
      if (!success) return;

      /** HANDLE RESPONSE **/
      std::string response = r->getModelPacked();
      client.acceptedSocket.send(response.c_str(), response.length());
    }
  } catch(const std::exception& e) {
    if (errno == 9) return;
    std::cout << "ERROR CLIENT PROXY WRITE: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CLIENT PROXY WRITE" << std::endl;
  }
}
