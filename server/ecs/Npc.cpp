#include "Npc.h"

NPC::NPC(EnemyData npcData, SkillsData skills) : 
  LiveEntity(npcData.position, npcData.healthAndManaData, skills),
  id(npcData.id),
  type(npcData.type),
  movement(npcData.movement)
  {}

NPC::~NPC(){}
