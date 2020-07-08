#ifndef _BUTTON_ENTITY_H
#define _BUTTON_ENTITY_H

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../sdl/SdlUtils.h"
#include "../sdl/LTexture.h"

class ButtonEntity: public Entity {
  public:
    ButtonEntity(
      LTexture* mainT,
      int xpos,
      int ypos,
      int w,
      int h,
      LTexture* activeT = nullptr);
    ButtonEntity(const ButtonEntity&) = delete;
    ButtonEntity& operator=(const ButtonEntity&) = delete;
    ButtonEntity&& operator=(ButtonEntity&& other);
    bool isActive();
    void handleClick(int xCoord, int yCoord);
    void handleClickClear();
    void paint(double scaleW, double scaleH) override;
    virtual void paint(
      const Camera &camera, double scaleW, double scaleH) override {}

  private:
    LTexture* mainT;
    LTexture* activeT = nullptr;
    LTexture* hoverT = nullptr;
    bool inside = false;
    bool click = false;
    int xpos;
    int ypos;
    int w;
    int h;
};

#endif
