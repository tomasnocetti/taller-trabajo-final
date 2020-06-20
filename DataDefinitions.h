#ifndef __DATADEF_H
#define __DATADEF_H

#include "definitions/MapDefinitions.h"
#include "definitions/NPCDefinitions.h"
#include "definitions/PlayerDefinitions.h"
#include <string>
#include <vector>

typedef enum {
  MOVE,
  BUY,
  DEPOSIT_GOLD,
  DEPOSIT_ITEM,
  ATTACK,
  CLOSE_SERVER,
  LOAD_PLAYER,
  AUTHENTICATE
} ActionTypeT;

typedef enum {
  PLAYER_GAME_MODEL,
  MAP_MODEL
} ResponseTypeT;

MSGPACK_ADD_ENUM(ActionTypeT)

typedef struct ParamData {
  std::string value;
  MSGPACK_DEFINE(value)
} ParamDataT;

struct InstructionData {
  ActionTypeT action;
  std::vector<ParamData> params;
  MSGPACK_DEFINE(action, params)
};

#endif
