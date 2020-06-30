#include "GameCron.h"
#include "ecs/Entity.h"
#include "GameConfig.h"
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
      runPlayerHealthAndMana(d->otherPlayers);

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
}

CronBQ& GameCron::getBQ() {
  return cronBQ;
}

void GameCron::runPlayersMovement(std::vector<OtherPlayersData>& players) {
  const GlobalConfig& c = GC::get();
  for (OtherPlayersData &player : players) {
    if (player.resurrection.resurrect == true){
      playerResurrection(player);
      continue;
    }
      
    if (player.movement.xDir == 0 &&
      player.movement.yDir == 0) continue;

    int x = player.position.x + player.movement.xDir * c.speed;
    int y = player.position.y + player.movement.yDir * c.speed;

    std::unique_ptr<Instruction> i(
      new PlayerSetCoordsInstruction(player.id, x, y));
    instructionQueue.push(std::move(i));
  }
}

void GameCron::playerResurrection(OtherPlayersData &player){
  if (player.resurrection.timeToResurrection 
    > std::chrono::system_clock::now()) return;

  std::unique_ptr<Instruction> i(
      new PlayerResurrecctionInstruction(
        player.id));
    instructionQueue.push(std::move(i));  
}

void GameCron::runPlayerHealthAndMana(std::vector<OtherPlayersData>& players){
  std::chrono::seconds sec(3);
  for (auto& it : players){
    if (((it.healthAndMana.currentHP == it.healthAndMana.totalHP) &&
      (it.healthAndMana.currentMP == it.healthAndMana.totalMP))
      || (it.healthAndMana.lastHealthIncrease + sec >
      std::chrono::system_clock::now()) || 
      (it.healthAndMana.currentHP <= 0)) continue;
      
      std::unique_ptr<Instruction> i(
        new PlayerIncreaseHealthInstruction(it.id));
        instructionQueue.push(std::move(i));

    if ((it.healthAndMana.meditating) && (it.healthAndMana.currentHP > 0)
      && (it.healthAndMana.lastManaIncrease + sec <
      std::chrono::system_clock::now())){
        std::unique_ptr<Instruction> ins(
          new IncreaseManaMeditationInstruction(it.id));
          instructionQueue.push(std::move(ins));
        continue;
    }

    if ((it.healthAndMana.currentMP == it.healthAndMana.totalMP)
      || (it.healthAndMana.lastManaIncrease + sec >
        std::chrono::system_clock::now()) || 
        (it.healthAndMana.currentMP <= 0)) continue;
      
      std::unique_ptr<Instruction> ins(
        new PlayerIncreaseManaInstruction(it.id));
        instructionQueue.push(std::move(ins));
  }
}

void GameCron::runNPCLogic(
  std::vector<EnemyData>& npcs,
  std::vector<OtherPlayersData>& players) {
  for (EnemyData &npc : npcs) {
    if (npc.healthAndManaData.currentHP <= 0){
      if (npc.healthAndManaData.nextRespawn < std::chrono::system_clock::now())
        NPCReSpawn(npc.id);
    }
    
    aliveNPCLogic(players, npc);
  }
}

void GameCron::aliveNPCLogic(std::vector<OtherPlayersData>& players, 
  EnemyData &npc){
    if (npc.healthAndManaData.currentHP <= 0) return;
    const GlobalConfig& c = GC::get();
    
    bool hasPlayerInRange = false;
    double minDistanceToPlayer = c.minDistanceNpc;

    double minDistanceToAttackPlayer = c.minDistanceToAttackPlayer;
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

    if (!hasPlayerInRange) return;
    moveNPC(npc.id, npc.position, playerPosition);    

    std::chrono::seconds sec(c.attackInterval);
    if (std::chrono::system_clock::now() < npc.lastAttack + sec) return;

    if (minDistanceToPlayer > minDistanceToAttackPlayer) return;
    NPCAttack(npc.id, playerPosition);
}

void GameCron::moveNPC(size_t id, PositionData& npc, PositionData& follow) {
  MovementData d = Entity::getPositionDirection(npc, follow);
  const GlobalConfig& c = GC::get();

  int x = npc.x + d.xDir * c.speedNpc;
  int y = npc.y + d.yDir * c.speedNpc;

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
