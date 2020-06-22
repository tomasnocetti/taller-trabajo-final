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
}

bool ClientProxy::isClose(){
  return !running;
}

ClientProxy::~ClientProxy(){}

ClientProxyRead::ClientProxyRead(ClientProxy& client) :
  client(client) {}

void ClientProxyRead::run(){
  try{
    while (client.running){
      InstructionData i = getInstruction();
      /** HANDLE **/
      handleInstruction(i);
    }
  } catch(const std::exception& e) {
    std::cout << "ERROR CLIENT PROXY: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CLIENT PROXY" << std::endl;
  }
}

InstructionData ClientProxyRead::getInstruction() {
  uint32_t sizeInstruction;
  client.acceptedSocket.receive((char*) &sizeInstruction, 4);

  sizeInstruction = from_big_end<uint32_t>(sizeInstruction);

  std::vector<char> res_message(sizeInstruction);

  client.acceptedSocket.receive(res_message.data(), sizeInstruction);
  std::string instruction(res_message.begin(), res_message.end());

  /* Código para mockear */
  msgpack::object_handle oh =
        msgpack::unpack(instruction.data(), instruction.size());
  msgpack::object deserialized = oh.get();
  InstructionData instructionData = deserialized.as<InstructionData>();
  std::cout << deserialized << std::endl;

  return instructionData;
}

void ClientProxyRead::handleInstruction(InstructionData& instruction) {
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
      break;
    case DEPOSIT_GOLD:
      break;
    case DEPOSIT_ITEM:
      break;
    case ATTACK:
      break;
    case CLOSE_SERVER:
      client.running = false;
      client.acceptedSocket.close();
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
    std::cout << "ERROR CLIENT PROXY: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CLIENT PROXY" << std::endl;
  }
}
