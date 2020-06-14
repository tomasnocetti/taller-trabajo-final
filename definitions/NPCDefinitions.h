#ifndef __NPCDEF_H
#define __NPCDEF_H

#include "EntityDefinitions.h"

typedef enum {
  GOBLIN,
  SKELETTON,
  ZOMBIE,
  SPIDER
} NPCClass;

struct EnemyData {
  PositionData position;
  NPCClass type;
};

#endif
