#include "ClientProxy.h"

#include <iostream>
#include <vector>
#include <unistd.h>

ClientProxy::ClientProxy(InstructionDataBQ &instructionQueue):
  running(true),
  playerId(0),
  readProxy(*this),
  instructionQueue(instructionQueue),
  clientBQ(1) {}

void ClientProxy::start(){
  readProxy.run();
}

void ClientProxy::setPlayerId(size_t id) {
  playerId = id;
}

UpdateClientsBQ& ClientProxy::getUpdateBQ() {
  return clientBQ;
}

void ClientProxy::stopPlaying(){
  running = false;
}

ClientProxy::~ClientProxy(){}

ClientProxyRead::ClientProxyRead(ClientProxy& client) : 
  client(client) {}

void ClientProxyRead::run(){
  /* Con este id, genero una nueva instrucción loadPlayer, y la pusheo
  a la instructionQueue para que el jugador sea dado de alta con sus
  respectivos datos de MainPlayerData almacenado en la base de datos. */
  size_t id = 4;
  sleep(2*id);
  std::cout << "Hola! Soy el cliento con id " << id << std::endl;

  client.setPlayerId(22);
  ParamData z = {"tomi123"};
  InstructionData auth = {AUTHENTICATE, {z}};
  handleInstruction(auth);
  
  std::cout << "Hola! Soy el cliento con id " << client.playerId << std::endl;
  while (client.running){
    /** READ FROM SOCKET BLOCKING **/
    ParamData x = {"100"};
    ParamData y = {"200"};
    InstructionData instruction = {MOVE, {x,y}};

    /** HANDLE **/
    handleInstruction(instruction);
  }
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
