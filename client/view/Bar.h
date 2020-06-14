#ifndef _BAR_H_
#define _BAR_H_

#include <SDL2/SDL.h>
#include <string>
#include "../sdl/LTexture.h"
#include "../sdl/SdlWindow.h"

class Bar {
	private:
		SDL_Rect destRect;
		LTexture texture;
		int maxValueWidth;

	public:
		Bar();
		void init(SdlWindow& window, std::string path, 
			int x, int y, int w, int h);
		void paint(int value, int maxValue);
};

#endif
