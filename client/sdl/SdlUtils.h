#ifndef _SDLUTILS_H_
#define _SDLUTILS_H_

#include <SDL2/SDL.h>

SDL_Rect sdlScaleRect(SDL_Rect& r, double scaleW, double scaleH);

SDL_Rect sdlDownscaleRect(SDL_Rect& rect, double scaleW, double scaleH);

bool inRect(SDL_Rect& rect, int x, int y);

#endif
