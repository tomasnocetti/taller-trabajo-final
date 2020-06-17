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
  CLOSE_SERVER,
  LOAD_PLAYER,
  AUTHENTICATE
} ActionTypeT;

struct ParamData {
  std::string value;
  //MSGPACK_DEFINE(value)
};

struct InstructionData {
  ActionTypeT action;
  std::vector<ParamData> params;
  //MSGPACK_DEFINE(playerId, params, action)
};

#endif
