#ifndef _MAPV_H_
#define _MAPV_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../sdl/LTexture.h"
#include "../sdl/SdlWindow.h"

#define MAIN_SCREEN_BASE_MAP_X 11
#define MAIN_SCREEN_BASE_MAP_Y 154
#define MAIN_SCREEN_BASE_MAP_W 542
#define MAIN_SCREEN_BASE_MAP_H 413

class Map {
	public:
		//Initializes variables
	  explicit Map(SdlWindow& window);
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;
    void paint();
		//Deallocates memory
		~Map();
	private:
		//The actual hardware texture
		SdlWindow& window;
    LTexture texture;
};

#endif
