#include "GameServer.h"

#include <utility>
#include <iostream>
#include <vector>
#include <chrono>

GameServer::GameServer(char* port) :
  running(true),
  cron(instructionQueue),
  game(cron.getBQ()),
  clientAcceptor(port, instructionQueue) {}

GameServer::~GameServer(){}

void GameServer::run(){
  clientAcceptor.start();
  cron.start();

  const int FPS = 40;
  std::chrono::milliseconds frameDelay(1000/FPS);
  std::chrono::system_clock::time_point frameStart =
    std::chrono::system_clock::now();

  while (running){
    std::unique_ptr<Instruction> instruction;
    bool success = instructionQueue.try_front_pop(instruction);
    if (!success) break;

    instruction->run(game);

    std::chrono::system_clock::time_point frameEnd =
      std::chrono::system_clock::now();
    std::chrono::milliseconds difference =
      std::chrono::duration_cast<std::chrono::milliseconds>
      (frameEnd - frameStart);

    game.propagateCronData();

    if (difference > frameDelay){
      game.propagate();
      frameStart = std::chrono::system_clock::now();
    }
  }
}

void GameServer::stop(){
  clientAcceptor.stop();
  running = false;
  instructionQueue.close();
  cron.stop();
  this->join();
}
