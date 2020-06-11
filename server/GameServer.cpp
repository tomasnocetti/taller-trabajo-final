#include "GameServer.h"
#include "ClientAcceptor.h"

#include <utility>
#include <iostream>

GameServer::GameServer() : isClose(false){}

GameServer::~GameServer(){}

void GameServer::init(){
/* Cargar todo lo que el servidor necesite 
     Cargar Mapa en memoria.
     Cargar Archivo con datos indexables del jugador.
     Cargar Definiciones.
*/
}

void GameServer::start(){
  ClientAcceptor acceptor(updateModel);
  acceptor.run();
  while (!isClose){
    InstructionData instruction;
    updateModel.try_pop(instruction);
    handleInstruction(instruction);
  }
}

void GameServer::handleInstruction(InstructionData &instruction){
  ActionTypeT action = instruction.action;
  std::cout << action << std::endl;
  switch (action)
  {
  case MOVE:
    std::cout << "Mover jugador a x:" << instruction.params.at(0).value 
    << " y:" << instruction.params.at(1).value << std::endl;
    break;
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

void GameServer::addActivePlayer(Player &player){
  std::unique_ptr<Player> p(&player);
  activePlayers.push_back(std::move(p));
}
