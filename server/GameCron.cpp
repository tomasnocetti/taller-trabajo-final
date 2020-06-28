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

void GameCron::stop() {
  running = false;
  cronBQ.close();
}

CronBQ& GameCron::getBQ() {
  return cronBQ;
}

void GameCron::runPlayersMovement(std::vector<OtherPlayersData>& players) {
  for (OtherPlayersData &player : players) {
    if (player.movement.xDir == 0 &&
      player.movement.yDir == 0) continue;

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
    /*
    if (npc.healthAndManaData.currentHP <= 0)
      NPCReSpawn(npc.id);
    */
   
    bool hasPlayerInRange = false;
    double minDistanceToPlayer = MIN_DISTANCE_NPC;

    double minDistanceToAttackPlayer = MIN_DISTANCE_TO_ATTACK_PLAYER;
    PositionData playerPosition;

    // Calcula la distancia minima a un jugador
    for (OtherPlayersData &player : players) {
      if (player.otherPlayerHealth <= 0) continue;
      double distance = Entity::getPositionDistance(
        npc.position, player.position);

      if (distance >= minDistanceToPlayer) continue;
      minDistanceToPlayer = distance;
      hasPlayerInRange = true;
      playerPosition = player.position;
    }

    if (!hasPlayerInRange) continue;
    moveNPC(npc.id, npc.position, playerPosition);    

    if (minDistanceToPlayer > minDistanceToAttackPlayer) continue;
    NPCAttack(npc.id, playerPosition);
  }
}

void GameCron::moveNPC(size_t id, PositionData& npc, PositionData& follow) {
  MovementData d = Entity::getPositionDirection(npc, follow);
  
  int x = npc.x + d.xDir * SPEED_NPC;
  int y = npc.y + d.yDir * SPEED_NPC;

  std::unique_ptr<Instruction> i(
      new NPCSetCoordsInstruction(id, x, y));
    instructionQueue.push(std::move(i));
}

void GameCron::NPCAttack(size_t npcId, PositionData& playerToAttack) {
  std::unique_ptr<Instruction> i(
      new NPCAttackInstruction(npcId, playerToAttack.x, playerToAttack.y));
    instructionQueue.push(std::move(i));
}

void GameCron::NPCReSpawn(size_t id){
  std::unique_ptr<Instruction> i(
      new NPCRespawnInstruction(id));
    instructionQueue.push(std::move(i));
}

GameCron::~GameCron() {}
