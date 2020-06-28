#ifndef _SHIELD_H_
#define _SHIELD_H_

#include <SDL2/SDL.h> 
#include "../sdl/LTexture.h"

class Shield {
	private:
		LTexture* texture;
		SDL_Rect forward;
    SDL_Rect backward;
    SDL_Rect side;

	public:
		Shield(LTexture* texture, int forwardX, int forwardY, int forwardW,
      int forwardH, int backX, int backY, int backW, int backH, int sideX,
      int sideY, int sideW, int sideH);
		void paint(int x, int y, double scaleW, double scaleH, 
			SDL_Rect* headFrame);
};

#endif
