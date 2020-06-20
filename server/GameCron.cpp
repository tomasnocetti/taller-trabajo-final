#include "GameCron.h"
#include <iostream>
#include <chrono>

GameCron::GameCron(InstructionBQ& instructionQueue) :
  instructionQueue(instructionQueue) {}

void GameCron::run() {
  try{
    while (running){
      std::cout << "RUNNING GAME CRON" << std::endl;

      runNPCLogic();

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  } catch(const std::exception& e) {
    std::cout << "ERROR CLIENT PROXY: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CLIENT PROXY" << std::endl;
  }
}

void GameCron::close() {
  running = false;
}

CronBQ& GameCron::getBQ() {
  return cronBQ;
}

void GameCron::runPlayersMovement() {
  std::cout << "RUNNING PLAYERS MOVEMENT" << std::endl;
  size_t playerId = 4;

  std::unique_ptr<Instruction> i(new MoveInstruction(playerId));
  instructionQueue.push(std::move(i));
}

void GameCron::runNPCLogic() {
  std::cout << "RUNNING NPC LOGIC" << std::endl;
}

GameCron::~GameCron() {}
