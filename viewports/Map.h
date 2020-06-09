#ifndef _MAPV_H_
#define _MAPV_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../sdl/LTexture.h"
// #include "../MapManager.h"
#include "../view/PlayerView.h"

#define MAIN_SCREEN_BASE_MAP_X 11
#define MAIN_SCREEN_BASE_MAP_Y 154
#define MAIN_SCREEN_BASE_MAP_W 542
#define MAIN_SCREEN_BASE_MAP_H 413

class Map : SdlViewport{
	public:
		//Initializes variables
	  Map(
      SdlWindow& window,
      int x = MAIN_SCREEN_BASE_MAP_X,
      int y = MAIN_SCREEN_BASE_MAP_Y,
      int w = MAIN_SCREEN_BASE_MAP_W,
      int h = MAIN_SCREEN_BASE_MAP_H);
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;
    void paint();

    void init();

    void handleEvent(const SDL_Event &e);

		//Deallocates memory
		~Map();
	private:
		//The actual hardware texture
    // MapManager mapmanager;
    PlayerView playerView;
    SDL_Rect camera;
    LTexture background;
};

#endif
