#include "Npc.h"
#include <iostream>

NPC::NPC(EnemyData npcData, SkillsData skills, size_t level) : 
  LiveEntity(npcData.position, npcData.healthAndManaData, skills, level),
  id(npcData.id),
  type(npcData.type),
  movement(npcData.movement){}

NPC::~NPC(){}

bool NPC::checkCollision(Entity& otherEntity) const{
  if (this->health.currentHP <= 0) return false;
  return Entity::checkCollision(otherEntity);
}

bool NPC::checkInRange(Entity& otherEntity, double distance) const{
  if (this->health.currentHP <= 0) return false;
  return Entity::checkInRange(otherEntity, distance);
}

bool NPC::attack(LiveEntity &entity, int xCoord, int yCoord) {
  PositionData attackZoneData = {
    xCoord,
    yCoord,
    ATTACK_NPC_ZONE_WIDTH,
    ATTACK_NPC_ZONE_HEIGHT};
  Entity attackZone(attackZoneData);

  bool canAttack = entity.checkCollision(attackZone);
  if (!canAttack) return false;

  int damage = skills.strength * level * 0.2;
  entity.rcvDamage(damage);

  return true;
}

int NPC::drop(unsigned int &seed){
  if (health.currentHP > 0) return 0;

  float random = ((float) rand_r(&seed)) / (float) RAND_MAX;
  float diff = 0.2;
  float r = random * diff;
  return r * health.totalHP;
}

std::unique_ptr<NPC> NPC::createNPC(size_t id, PositionData position, 
  size_t level, NPCClass npcType) {
    EnemyData data;
    data.id = id;
    data.position = position;
    data.movement.xDir = 0;
    data.movement.yDir = 0;
    data.type = npcType;
    data.healthAndManaData = {100, 100, 0, 0};
    
    SkillsData skills = {10, 10, 10};
  
    std::unique_ptr<NPC> npc(new NPC(data, skills, level));

    return npc;
}

size_t NPC::idGenerator = 0;

size_t NPC::getNewId(){
  NPC::idGenerator ++;
  return NPC::idGenerator;
}
