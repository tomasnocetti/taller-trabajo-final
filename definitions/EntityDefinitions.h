#ifndef __ENTITYDEF_H
#define __ENTITYDEF_H

#include <msgpack.hpp>

struct PositionData {
  int x;
  int y;
  int w;
  int h;
  MSGPACK_DEFINE(x, y, w, h)
};

struct MovementData {
  int xDir;
  int yDir;
  MSGPACK_DEFINE(xDir, yDir)
};

struct HealthAndManaData {
  int totalHP;
  int currentHP;
  int totalMP;
  int currentMP;
  MSGPACK_DEFINE(totalHP, currentHP, totalMP, currentMP)
};

#endif
