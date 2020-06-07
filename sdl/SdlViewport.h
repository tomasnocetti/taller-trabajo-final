#pragma once

#include <SDL2/SDL.h>
#include "SdlWindow.h"

class SdlViewport {
  public:
    SdlViewport(SdlWindow& window, int x, int y, int w, int h, int scale = 1);
    SdlViewport(const SdlViewport&) = delete;
    SdlViewport& operator=(const SdlViewport&) = delete;
    SdlViewport&& operator=(SdlViewport&& other);
    void setViewport();
    void fit();
    ~SdlViewport();
  private:
    protected: SdlWindow& window;
    int scale;
    SDL_Rect srcViewport;
    SDL_Rect destViewport;
};