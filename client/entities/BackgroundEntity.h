#ifndef _BACKGROUND_ENTITY_H_
#define _BACKGROUND_ENTITY_H_

#include <string>
#include "Entity.h"
#include "../sdl/LTexture.h"

class BackgroundEntity: public Entity {
  public:
    LTexture* texture;
    SDL_Rect srcRect, destRect;

    BackgroundEntity(
      LTexture* background);
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera) override {};
};

#endif
