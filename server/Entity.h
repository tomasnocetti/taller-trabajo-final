#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include "../DataDefinitions.h"

class Entity{
  private:
    EntityDataT entityData;
  public:
    Entity();
    ~Entity();
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;
    virtual void create();
    virtual void attack();
    virtual void move();
};

#endif
