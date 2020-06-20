#include "SdlUtils.h"

SDL_Rect sdlScaleRect(SDL_Rect& r, double scaleW, double scaleH){
  return SDL_Rect({
    static_cast<int>(
      ceil(static_cast<double>(r.x) * scaleW)),
    static_cast<int>(
      ceil(static_cast<double>(r.y) * scaleH)),
    static_cast<int>(
      ceil(static_cast<double>(r.w) * scaleW)),
    static_cast<int>(
      ceil(static_cast<double>(r.h) * scaleH))
  });
}

bool sdlInRect(SDL_Rect& rect, int x, int y){
  return (x < rect.x) ||
    (x > (rect.x + rect.w)) ||
    (y < rect.y) ||
    (y > (rect.y + rect.h));
}
