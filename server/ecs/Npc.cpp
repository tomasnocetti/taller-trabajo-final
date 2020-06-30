#include "Npc.h"
#include "../GameConfig.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include "../services/ChatManager.h"

NPC::NPC(EnemyData npcData, SkillsData skills, size_t level) :
  LiveEntity(npcData.position, npcData.healthAndManaData, skills, level,
    npcData.id),
  type(npcData.type),
  movement(npcData.movement){
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

  bool dodged = Equations::dodgeAttack(entity.skills.agility);
  if (dodged){
    return true;
  }

  int damage = Equations::NPCDamage(level, skills.strength);
  entity.rcvDamage(damage);

  return true;
}

void NPC::rcvDamage(int &damage) {
  bool dodged = Equations::dodgeAttack(skills.agility);
  if (dodged){
    damage = -1;
    return;
  }
  health.currentHP -= damage;
}

int NPC::drop(unsigned int &seed){
  if (health.currentHP > 0) return 0;
  const GlobalConfig& c = GC::get();

  return health.totalHP * Equations::randomFloat(0, c.npcRandomDrop);
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
    data.movement.xDir = 0;
    data.movement.yDir = 0;
    data.type = npcType;
    data.healthAndManaData = {
      c.npcInitHealthPoints,
      c.npcInitHealthPoints,
      0,
      0,
      std::chrono::system_clock::now()};
    data.lastAttack = std::chrono::system_clock::now();

    SkillsData skills = {
      c.npcInitSkills, c.npcInitSkills, c.npcInitSkills};

    std::unique_ptr<NPC> npc(new NPC(data, skills, level));

    return npc;
}

size_t NPC::idGenerator = 0;

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
