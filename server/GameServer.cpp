#include "GameServer.h"

#include <utility>
#include <iostream>
#include <vector>

GameServer::GameServer(char* port, char* mapPath) :
  running(true),
  cron(instructionQueue),
  game(mapPath, cron.getBQ()),
  clientAcceptor(port, instructionQueue) {}

GameServer::~GameServer(){}

void GameServer::init(){
  /* Cargar todo lo que el servidor necesite
    Cargar Mapa en memoria.
    Cargar Archivo con datos indexables del jugador.
    Cargar Definiciones.
  */
}

void GameServer::run(){
  clientAcceptor.start();
  cron.start();
  //game.addNPCS();
  while (running){
    std::unique_ptr<Instruction> instruction;
    bool success = instructionQueue.try_front_pop(instruction);
    
    if (!success) break;
    
    instruction->run(game);
    game.propagate();
  }
}

void GameServer::stop(){
  running = false;
  instructionQueue.close();
  clientAcceptor.stop();
  cron.stop();
  this->join();
}
