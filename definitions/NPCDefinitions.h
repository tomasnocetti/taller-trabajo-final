#ifndef __NPCDEF_H
#define __NPCDEF_H

#include "EntityDefinitions.h"

typedef enum {
  GOBLIN,
  SKELETON,
  ZOMBIE,
  SPIDER
} NPCClass;

MSGPACK_ADD_ENUM(NPCClass)

struct EnemyData {
  MovementData movement;
  PositionData position;
  NPCClass type;
  size_t id;
  MSGPACK_DEFINE(movement, position, type)
};

#endif
