#ifndef _HEAD_WEAR_H_
#define _HEAD_WEAR_H_

#include <SDL2/SDL.h> 
#include "../sdl/LTexture.h"

class HeadWear {
	public:
		virtual void paint(int x, int y, double scaleW, double scaleH, 
			SDL_Rect* headFrame) = 0;
};

class IronHelmet : public HeadWear {
	public:
		IronHelmet(LTexture* texture);
		void paint(int x, int y, double scaleW, double scaleH, 
			SDL_Rect* headFrame);
	private:
		LTexture* texture;
};

class MagicHat : public HeadWear {
	public:
		MagicHat(LTexture* texture);
		void paint(int x, int y, double scaleW, double scaleH, 
			SDL_Rect* headFrame);
	private:
		LTexture* texture;
};

#endif
