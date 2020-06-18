#ifndef _SDLUTILS_H_
#define _SDLUTILS_H_

#include <SDL2/SDL.h>

SDL_Rect sdlScaleRect(SDL_Rect& r, double scaleW, double scaleH);

bool sdlInRect(SDL_Rect& r, int x, int y);

#endif
