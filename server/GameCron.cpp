#include "GameCron.h"
#include "ecs/Entity.h"
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
      runNPCLogic(d->npcs, d->otherPlayers);

      std::this_thread::sleep_for(std::chrono::milliseconds(60));
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
    // std::cout << "Player " << player.id << " is moving? " std::endl;
    if (player.movement.xDir == 0 &&
      player.movement.yDir == 0) continue;
    std::cout << "RUNNING PLAYERS MOVEMENT" << std::endl;

    int x = player.position.x + player.movement.xDir * SPEED;
    int y = player.position.y + player.movement.yDir * SPEED;

    std::unique_ptr<Instruction> i(
      new PlayerSetCoordsInstruction(player.id, x, y));
    instructionQueue.push(std::move(i));
  }
}

void GameCron::runNPCLogic(
  std::vector<EnemyData>& npcs,
  std::vector<OtherPlayersData>& players) {
  for (EnemyData &npc : npcs) {
    bool hasPlayerInRange = false;
    double minDistanceToPlayer = MIN_DISTANCE_NPC;
    PositionData positionTofollow;

    // Calcula la distancia minima a un jugador
    for (OtherPlayersData &player : players) {
      double distance = Entity::getPositionDistance(
        npc.position, player.position);
      if (distance >= minDistanceToPlayer) continue;
      hasPlayerInRange = true;
      positionTofollow = player.position;
    }

    if (!hasPlayerInRange) continue;
    // moveNPC(npc.id, npc.position, positionTofollow);
  }
}

// void GameCron::moveNPC(size_t id, PositionData& npc, PositionData& follow) {

// }

GameCron::~GameCron() {}
