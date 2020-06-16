#ifndef _TILE_ENTITY_H_
#define _TILE_ENTITY_H_

#include <string>
#include "Entity.h"
#include "../sdl/LTexture.h"

class TileEntity: public Entity {
  public:
    LTexture* texture;
    SDL_Rect srcRect, destRect;

    TileEntity(LTexture* stexture,
    int srcX,
    int srcY,
    int xpos,
    int ypos,
    int tsize,
    int tscale,
    std::string id);
    void paint(const Camera &camera, double scaleW, double scaleH) override;
    void paint() override {};
    void paint(const Camera &camera) override {};
};

#endif
