#ifndef __ENTITYDEF_H
#define __ENTITYDEF_H

struct PositionData {
  int x;
  int y;
  int w;
  int h;
};

struct MovementData {
  int xDir;
  int yDir;
  int speed;
  bool isMoving;
};

#endif
