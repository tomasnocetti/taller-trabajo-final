#include "Npc.h"

NPC::NPC(EnemyData npcData, HealthAndManaData points) : 
  LiveEntity(npcData.position, points),
  id(npcData.id),
  type(npcData.type),
  movement(npcData.movement)
  {}

NPC::~NPC(){}
