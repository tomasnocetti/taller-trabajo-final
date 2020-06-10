#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

typedef struct EntityData{
  uint32_t x;
  uint32_t y;
  bool isDead;
  uint32_t lifePoints;
}entityData_t;

class Entity{
private:
  entityData_t entityData;
public:
  Entity();
  virtual void create();
  virtual void attack();
  virtual void move();
  ~Entity();
};

#endif
