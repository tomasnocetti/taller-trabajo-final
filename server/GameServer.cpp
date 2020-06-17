#include "GameServer.h"
#include "ClientAcceptor.h"

#include <utility>
#include <iostream>
#include <vector>

GameServer::GameServer() : running(true) {}

GameServer::~GameServer(){}

void GameServer::init(){
  /* Cargar todo lo que el servidor necesite
    Cargar Mapa en memoria.
    Cargar Archivo con datos indexables del jugador.
    Cargar Definiciones.
  */
}

void GameServer::start(){
  ClientAcceptor acceptor(instructionQueue);
  acceptor.start();
  int i = 0;

  while (running && i<1000){
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
