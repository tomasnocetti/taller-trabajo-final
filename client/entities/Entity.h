#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <memory>
#include "../view/Camera.h"

class Entity {
  public:
    int x;
    int y;
    virtual void paint() = 0;
    virtual void paint(const Camera &camera) = 0;
    //esto habria que sacarlo
    virtual void move(int x, int y) {} 
    virtual ~Entity() {}
};

using EntityList = std::vector<std::unique_ptr<Entity>>;

#endif
