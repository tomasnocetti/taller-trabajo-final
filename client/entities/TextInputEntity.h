#ifndef _TEXT_INPUT_ENTITY_H
#define _TEXT_INPUT_ENTITY_H

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../sdl/SdlUtils.h"
#include "../sdl/LTexture.h"

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

class TextInputEntity: public Entity {
  public:
    TextInputEntity(
      LTexture* texture,
      TTF_Font* font,
      int xpos,
      int ypos);
    TextInputEntity(const TextInputEntity&) = delete;
    TextInputEntity& operator=(const TextInputEntity&) = delete;
    TextInputEntity&& operator=(TextInputEntity&& other);
    void handleEvent(const SDL_Event &e);
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera, 
      double scaleW, double scaleH) override {}

  private:
    LTexture* texture;
    TTF_Font* font;
    std::string input;
    bool inside = false;
    double lWScale = 1;
    double lHScale = 1;
    int size;
    int xpos;
    int ypos;
};

#endif
