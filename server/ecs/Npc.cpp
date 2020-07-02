#include "Npc.h"
#include "../GameConfig.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include "../services/ChatManager.h"

NPC::NPC(EnemyData npcData, size_t level) :
  LiveEntity(
    npcData.position,
    npcData.healthAndManaData,
    level,
    npcData.id),
  type(npcData.type){
    spawnPosition = npcData.position;
}

bool NPC::checkCollision(Entity& otherEntity) const{
  if (health.currentHP <= 0 &&
    health.nextRespawn >= std::chrono::system_clock::now()) return false;
  return Entity::checkCollision(otherEntity);
}

bool NPC::checkInRange(Entity& otherEntity, double distance) const{
  if (this->health.currentHP <= 0) return false;
  return Entity::checkInRange(otherEntity, distance);
}

bool NPC::attack(LiveEntity &entity, int xCoord, int yCoord) {
  const GlobalConfig& c = GC::get();
  PositionData attackZoneData = {
    xCoord - c.attackNpcZoneWidth / 2,
    yCoord - c.attackNpcZoneHeight / 2,
    c.attackNpcZoneWidth,
    c.attackNpcZoneHeight};
  Entity attackZone(attackZoneData);

  bool canAttack = entity.checkCollision(attackZone);
  if (!canAttack) return false;

  lastAttack = std::chrono::system_clock::now();

  int damage = Equations::NPCDamage(level);
  entity.rcvDamage(damage);

  return true;
}

void NPC::rcvDamage(int &damage) {
  bool critickAttack = Equations::criticAttack();
  if (critickAttack){
    damage = damage * 2;
    health.currentHP -= damage;
    return;
  }

  bool dodged = Equations::dodgeAttackNPC();
  if (dodged){
    damage = -1;
    return;
  }
  health.currentHP -= damage;
}

bool NPC::drop(DropItemData &drop){
  if (health.currentHP > 0) return false;
  const GlobalConfig& c = GC::get();
  double probDrop = Equations::randomFloat(0, 1);
  drop.amount = 1;
  drop.position = position;

  if (probDrop <= c.npcDropGold){
    double gold = Equations::randomFloat(c.npcDropGoldRandMinValue,
      c.npcDropGoldRandMaxValue) * health.totalHP;
    drop.id = c.goldItemId;
    drop.amount = int(gold);
    return true;
  }

  if ((probDrop > c.npcDropGold) && (probDrop <=
    (c.npcDropGold + c.npcDropPotion))){
      int potion = Equations::random(0, 1);
      if (potion == 1){
        drop.id = c.potionsToDropNPC[0];
      }else{
        drop.id = c.potionsToDropNPC[1];
      }
      return true;
  }

  if ((probDrop > c.npcDropGold + c.npcDropPotion) &&
    (probDrop <= c.npcDropGold + c.npcDropPotion + c.npcDropItem)){
      drop.id = Equations::random(1, c.itemsToDropNPC.size());
      return true;
  }

  return false;
}

void NPC::setNextRespawn(){
  const GlobalConfig& c = GC::get();
  std::chrono::seconds sec(c.respawnTimeNpc);
  health.nextRespawn = std::chrono::system_clock::now() + sec;
}

std::unique_ptr<NPC> NPC::createNPC(size_t id, PositionData position,
  size_t level, NPCClass npcType) {
    EnemyData data;
    const GlobalConfig& c = GC::get();
    data.id = id;
    data.position = position;
    data.type = npcType;
    data.healthAndManaData = {
      c.npcInitHealthPoints,
      c.npcInitHealthPoints,
      0,
      0,
      std::chrono::system_clock::now()};
    data.lastAttack = std::chrono::system_clock::now();

    std::unique_ptr<NPC> npc(new NPC(data, level));

    return npc;
}

size_t NPC::idGenerator = 5000;

size_t NPC::getNewId(){
  NPC::idGenerator ++;
  return NPC::idGenerator;
}

void NPC::setEnemyData(EnemyData &enemy){
  enemy.movement = movement;
  enemy.position = position;
  enemy.type = type;
  enemy.id = id;
  enemy.healthAndManaData = health;
  enemy.lastAttack = lastAttack;
}
