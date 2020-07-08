#ifndef _TEXT_INPUT_ENTITY_H
#define _TEXT_INPUT_ENTITY_H

#include "Entity.h"
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "../sdl/SdlUtils.h"
#include "../sdl/LTexture.h"

class TextInputEntity: public Entity {
  public:
    TextInputEntity(
      LTexture* texture,
      TTF_Font* font,
      int xpos,
      int ypos,
      int maxWidth,
      int maxHeight);
    TextInputEntity(const TextInputEntity&) = delete;
    TextInputEntity& operator=(const TextInputEntity&) = delete;
    TextInputEntity&& operator=(TextInputEntity&& other);
    std::string getInput();
    void clearInput();
    void activateInput(const std::string& c);
    void handleClick(int xCoord, int yCoord);
    void handleInput(const SDL_Event &e);
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera, 
      double scaleW, double scaleH) override {}

  private:
    LTexture* texture;
    TTF_Font* font;
    std::string input;
    bool inside = false;
    int lastRenderTime = 0;
    double lWScale = 1;
    double lHScale = 1;
    int size;
    int xpos;
    int ypos;
    int maxWidth;
    int maxHeight;
};

#endif
