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

void GameServer::start(){
  clientAcceptor.start();
  cron.start();
  int i = 0;

  while (running && i<10000){
    i++;

    std::unique_ptr<Instruction> instruction;
    instructionQueue.try_front_pop(instruction);

    instruction->run(game);
    game.propagate();
  }
}

void GameServer::close(){
  running = false;
}
