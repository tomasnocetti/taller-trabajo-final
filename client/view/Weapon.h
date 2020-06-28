#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <SDL2/SDL.h> 
#include "../sdl/LTexture.h"

class Weapon {
	private:
		LTexture* texture;
		SDL_Rect forward;
    SDL_Rect backward;
    SDL_Rect side;
    int forwardXOffset, forwardYOffset;
    int backXOffset, backYOffset;
    int sideXOffset, sideYOffset;

	public:
		Weapon(LTexture* texture, int forwardX, int forwardY, int forwardW,
      int forwardH, int backX, int backY, int backW, int backH, int sideX,
      int sideY, int sideW, int sideH, int forwardXOffset, 
      int forwardYOffset, int backXOffset, int backYOffset, int sideXOffset, 
      int sideYOffset);
		void paint(int x, int y, double scaleW, double scaleH, 
			SDL_Rect* headFrame);
};

#endif
