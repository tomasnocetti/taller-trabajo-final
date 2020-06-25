#ifndef _HEAD_WEAR_H_
#define _HEAD_WEAR_H_

#include <SDL2/SDL.h> 
#include "../sdl/LTexture.h"

class HeadWear {
	private:
		LTexture* texture;
		int xOffsetYAxis;
		int yOffsetYAxis;
		int xOffsetXAxis;
		int yOffsetXAxis;

	public:
		HeadWear(LTexture* texture, int xOffsetYAxis, int yOffsetYAxis, 
			int xOffsetXAxis, int yOffsetXAxis);
		void paint(int x, int y, double scaleW, double scaleH, 
			SDL_Rect* headFrame);
};

#endif
