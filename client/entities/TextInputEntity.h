#ifndef _TEXT_INPUT_ENTITY_H
#define _TEXT_INPUT_ENTITY_H

#include "Entity.h"
#include <SDL2/SDL_ttf.h>
#include "../sdl/LTexture.h"

class TextInputEntity: public Entity {
  public:
    TextInputEntity(
      LTexture* texture,
      TTF_Font* font,
      int size,
      int xpos,
      int ypos);
    TextInputEntity(const TextInputEntity&) = delete;
    TextInputEntity& operator=(const TextInputEntity&) = delete;
    TextInputEntity&& operator=(TextInputEntity&& other);
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera) override {};

  private:
    LTexture* texture;
    TTF_Font* font;
    int size;
    int xpos;
    int ypos;
};

#endif
