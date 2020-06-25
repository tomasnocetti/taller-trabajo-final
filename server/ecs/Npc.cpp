#include "Npc.h"
#include <iostream>

NPC::NPC(EnemyData npcData, SkillsData skills, size_t level) : 
  LiveEntity(npcData.position, npcData.healthAndManaData, skills, level),
  id(npcData.id),
  type(npcData.type),
  movement(npcData.movement),
  seed(0)
  {}

NPC::~NPC(){}

bool NPC::checkCollision(Entity& otherEntity) const{
  if (this->health.currentHP <= 0) return false;
  return Entity::checkCollision(otherEntity);
}

bool NPC::checkInRange(Entity& otherEntity, double distance) const{
  if (this->health.currentHP <= 0) return false;
  return Entity::checkInRange(otherEntity, distance);
}

int NPC::attack(LiveEntity &entity, int xCoord, int yCoord) {
  return 0;
}

int NPC::deathDrop(){
  float random = ((float) rand_r(&seed)) / (float) RAND_MAX;
  float diff = 2 - 1;
  float r = random * diff;
  std::cout << "Numero random generado para el drop: " << r << std::endl;
  return 1 * health.totalHP;
}
