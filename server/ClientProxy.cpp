#include "ClientProxy.h"

#include <iostream>
#include <vector>
#include <unistd.h>

ClientProxy::ClientProxy(InstructionBQ &instructionQueue):
  running(true),
  authenticated(false),
  playerId(0),
  readProxy(*this),
  writeProxy(*this),
  instructionQueue(instructionQueue) {}

void ClientProxy::start(){
  readProxy.run();
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
  /** READ FROM SOCKET BLOCKING **/
  ParamData x = {"100"};
  ParamData y = {"200"};
  InstructionData instruction = {MOVE, {x,y}};

  return instruction;
}

void ClientProxyRead::handleInstruction(InstructionData& instruction) {
  ActionTypeT action = instruction.action;
  std::unique_ptr<Instruction> i;

  switch (action) {
    case AUTHENTICATE:
      i = std::unique_ptr<Instruction>(
        new AuthInstruction(client, instruction.params[0].value));
      client.instructionQueue.push(std::move(i));
      break;
    case MOVE:
      i = std::unique_ptr<Instruction>(new MoveInstruction(client.playerId));
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
      std::cout << "Se cerrará el server." << std::endl;
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
    while (true){

      std::unique_ptr<Response> r;
      bool success = client.responseBQ.try_front_pop(r);
      if (!success) return;

      /** HANDLE RESPONSE **/
      sendResponse(std::move(r));
    }
  } catch(const std::exception& e) {
    std::cout << "ERROR CLIENT PROXY: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CLIENT PROXY" << std::endl;
  }
}

void ClientProxyWrite::sendResponse(std::unique_ptr<Response>) {
  // HANDLE SENDING
}