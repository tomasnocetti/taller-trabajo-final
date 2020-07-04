#ifndef __NPCDEF_H
#define __NPCDEF_H

#include "EntityDefinitions.h"

typedef enum {
  GOBLIN = 'G',
  SKELETON = 'S',
  ZOMBIE = 'Z',
  SPIDER = 'A'
} NPCClass;

MSGPACK_ADD_ENUM(NPCClass)

struct EnemyData {
  MovementData movement;
  PositionData position;
  NPCClass type;
  size_t id;
  HealthAndManaData healthAndManaData;
  std::chrono::system_clock::time_point lastAttack;
  MSGPACK_DEFINE(movement, position, type, id, healthAndManaData)
};

#endif
