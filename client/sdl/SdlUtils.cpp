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

SDL_Rect sdlDownscaleRect(SDL_Rect& rect, double scaleW, double scaleH){
  return sdlScaleRect(rect, 1/scaleW, 1/scaleH);
}
