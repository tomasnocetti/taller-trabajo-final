#include "GameServer.h"
#include "ClientAcceptor.h"

#include <utility>
#include <iostream>

GameServer::GameServer() : isClose(false), activePlayers(0) {}

GameServer::~GameServer(){}

void GameServer::init(){
/* Cargar todo lo que el servidor necesite 
     Cargar Mapa en memoria.
     Cargar Archivo con datos indexables del jugador.
     Cargar Definiciones.
*/
}

void GameServer::start(){
  ClientAcceptor acceptor(instructionQueue, activePlayers);
  acceptor.start();
  while (!isClose){
    InstructionData instruction;
    instructionQueue.try_front_pop(instruction);
    handleInstruction(instruction);
  }
}

void GameServer::handleInstruction(InstructionData &instruction){
  ActionTypeT action = instruction.action;
  switch (action)
  {
    case MOVE:
      std::cout << "Mover jugador a x:" << instruction.params.at(0).value 
      << " y:" << instruction.params.at(1).value << std::endl;
      break;
    case BUY:
      std::cout << "El jugador quiere comprar " << 
      instruction.params.at(0).value << std::endl;
      break;
    case DEPOSIT_GOLD:
      std::cout << "EL jugador quiere depositar " << 
      instruction.params.at(0).value << " de oro." << std::endl;
      break;
    case DEPOSIT_ITEM: 
      std::cout << "El jugador quiere depositar un//una" << 
      instruction.params.at(0).value << std::endl;
      break;
    case ATTACK:
      std::cout << "El jugador quiere atacar a " << 
      instruction.params.at(0).value << std::endl;
    case CLOSE_SERVER:
      std::cout << "Se cerrará el server." << std::endl;
      close();  
      break;
    default:
      std::cout << "El jugador quiere realizar otra accion. " << std::endl;
      break;
  }
}

void GameServer::close(){
  isClose = true;
  // cerrar socket
}
