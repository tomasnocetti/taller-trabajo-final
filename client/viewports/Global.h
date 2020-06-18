#ifndef _GLOBALV_H_
#define _GLOBALV_H_

#include <string>
#include "../entities/Entity.h"
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"

#define MAIN_SCREEN_BASE_X 0
#define MAIN_SCREEN_BASE_Y 0
#define MAIN_SCREEN_BASE_W 800
#define MAIN_SCREEN_BASE_Global_H 600

class Global : SdlViewport {
	public:
		//Initializes variables
	  explicit Global(SdlWindow& window);
    Global(const Global&) = delete;
    Global& operator=(const Global&) = delete;
    void paint(EntityList& entities);
		//Deallocates memory
		~Global();
	private:
    // LTexture texture;
};

#endif
