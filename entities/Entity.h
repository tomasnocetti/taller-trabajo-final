#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <memory>
#include "../view/Camera.h"

class Entity {
  private:
    friend class Map;
  protected:
    int x;
    int y;

  public:
    virtual void paint(const Camera &camera) = 0;
    //esto tiene que irse:
    //virtual int getX() = 0;
    //virtual int getY() = 0;
    virtual ~Entity() {}
};

using EntityList = std::vector<std::unique_ptr<Entity>>;

#endif
