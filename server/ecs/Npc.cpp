#include "Npc.h"

NPC::NPC(EnemyData npcData, SkillsData skills, size_t level) : 
  LiveEntity(npcData.position, npcData.healthAndManaData, skills, level),
  id(npcData.id),
  type(npcData.type),
  movement(npcData.movement)
  {}

NPC::~NPC(){}

bool NPC::checkCollision(Entity& otherEntity) const{
  if (this->health.currentHP < 0) return false;
  return Entity::checkCollision(otherEntity);
}

bool NPC::checkInRange(Entity& otherEntity, double distance) const{
  if (this->health.currentHP < 0) return false;
  return Entity::checkInRange(otherEntity, distance);
}

int NPC::attack(LiveEntity &entity, int xCoord, int yCoord) {
  return 0;
}
