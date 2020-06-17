#ifndef _BUTTON_ENTITY_H
#define _BUTTON_ENTITY_H

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../sdl/SdlUtils.h"
#include "../sdl/LTexture.h"

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

class ButtonEntity: public Entity {
  public:
    ButtonEntity(
      LTexture* mainT,
      int xpos,
      int ypos,
      LTexture* activeT = nullptr,
      LTexture* hoverT = nullptr);
    ButtonEntity(const ButtonEntity&) = delete;
    ButtonEntity& operator=(const ButtonEntity&) = delete;
    ButtonEntity&& operator=(ButtonEntity&& other);
    void handleEvent(const SDL_Event &e);
    void paint(double scaleW, double scaleH) override;
    void paint(const Camera &camera) override {};

  private:
    LTexture* mainT;
    LTexture* activeT = nullptr;
    LTexture* hoverT = nullptr;
    bool inside = false;
    bool click = false;
    double lWScale = 1;
    double lHScale = 1;
    int xpos;
    int ypos;
};

#endif
