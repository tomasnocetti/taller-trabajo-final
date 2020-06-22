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
  bool isMoving;
  MSGPACK_DEFINE(xDir, yDir, isMoving)
};

#endif
