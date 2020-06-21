#include "GameCron.h"
#include <iostream>
#include <chrono>
#include <vector>

GameCron::GameCron(InstructionBQ& instructionQueue) :
  running(true),
  instructionQueue(instructionQueue) {}

void GameCron::run() {
  try{
    while (running){
      std::unique_ptr<CronGameModelData> d;

      bool success = cronBQ.try_front_pop(d);
      if (!success) continue;

      std::cout << "RUNNING GAME CRON" << std::endl;
      runPlayersMovement(d->otherPlayers);

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  } catch(const std::exception& e) {
    std::cout << "ERROR CRON GAME: " << e.what() << std::endl;
  } catch(...) {
    std::cout << "UNKOWN ERROR CRON GAME." << std::endl;
  }
}

void GameCron::close() {
  running = false;
}

CronBQ& GameCron::getBQ() {
  return cronBQ;
}

void GameCron::runPlayersMovement(std::vector<OtherPlayersData>& players) {
  for (OtherPlayersData &player : players) {
    std::cout << "Player " << player.id << " is moving? " << 
      player.movement.isMoving << std::endl;
    if (! player.movement.isMoving) continue;
    std::cout << "RUNNING PLAYERS MOVEMENT" << std::endl;

    int x = player.position.x + player.position.x * player.movement.speed;
    int y = player.position.y + player.position.y * player.movement.speed;

    std::unique_ptr<Instruction> i(
      new PlayerSetCoordsInstruction(player.id, x, y));
    instructionQueue.push(std::move(i));
  }
}

void GameCron::runNPCLogic() {
  std::cout << "RUNNING NPC LOGIC" << std::endl;
}

GameCron::~GameCron() {}
