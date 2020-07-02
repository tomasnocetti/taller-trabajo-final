#ifndef _DROP_ENTITY_H_
#define _DROP_ENTITY_H_

#include <string>
#include "Entity.h"
#include "../sdl/LTexture.h"

class DropEntity: public Entity {
  private:
    LTexture* texture;
    SDL_Rect destRect;

  public:
    DropEntity(LTexture* texture, int x, int y, int w, int h);
    void setImage(LTexture* texture);
    void move(int x, int y) override;
    void paint(double scaleW, double scaleH) override {}
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override;
};

#endif
