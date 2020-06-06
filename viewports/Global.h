#ifndef _GLOBALV_H_
#define _GLOBALV_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../sdl/LTexture.h"
#include "../sdl/SdlWindow.h"

#define MAIN_SCREEN_BASE_X 0
#define MAIN_SCREEN_BASE_Y 0
#define MAIN_SCREEN_BASE_W 800
#define MAIN_SCREEN_BASE_Global_H 600

#define MAIN_SCREEN_PATH "assets/main-screen.jpg"

class Global {
	public:
		//Initializes variables
	  explicit Global(SdlWindow& window);
    Global(const Global&) = delete;
    Global& operator=(const Global&) = delete;
    void paint();
		//Deallocates memory
		~Global();
	private:
		//The actual hardware texture
		SdlWindow& window;
    LTexture texture;
};

#endif
