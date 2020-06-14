#ifndef __NPCDEF_H
#define __NPCDEF_H

#include "EntityDefinitions.h"

typedef enum {
  GOBLIN,
  SKELETON,
  ZOMBIE,
  SPIDER
} NPCClass;

struct EnemyData {
  PositionData position;
  NPCClass type;
};

#endif
