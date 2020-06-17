#ifndef __DATADEF_H
#define __DATADEF_H

#include "definitions/MapDefinitions.h"
#include "definitions/NPCDefinitions.h"
#include "definitions/PlayerDefinitions.h"
#include <string>
#include <vector>
#include <msgpack.hpp>

typedef enum {
  MOVE,
  BUY,
  DEPOSIT_GOLD,
  DEPOSIT_ITEM,
  ATTACK,
  CLOSE_SERVER
} ActionTypeT;

MSGPACK_ADD_ENUM(ActionTypeT)

typedef struct ParamData {
  std::string value;
  MSGPACK_DEFINE(value)
} ParamDataT;

typedef struct InstructionData {
  size_t playerId;
  ActionTypeT action;
  std::vector<ParamData> params;
  MSGPACK_DEFINE(playerId, action, params)
} IntructionDataT;

typedef struct GameModel{
  std::string action;
} GameModelT;

#endif
