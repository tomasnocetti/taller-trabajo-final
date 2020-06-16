#ifndef _SDLUTILS_H_
#define _SDLUTILS_H_

#include <SDL2/SDL.h>

SDL_Rect sdlScaleRect(SDL_Rect r, double scaleW, double scaleH) {
  return SDL_Rect({
    static_cast<int>(
      round(static_cast<double>(r.x) * scaleW)),
    static_cast<int>(
      round(static_cast<double>(r.y) * scaleH)),
    static_cast<int>(
      round(static_cast<double>(r.w) * scaleW)),
    static_cast<int>(
      round(static_cast<double>(r.h) * scaleH))
  });
}

#endif
