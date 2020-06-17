#ifndef _MAPV_H_
#define _MAPV_H_

#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../view/Camera.h"
#include "../entities/Entity.h"
#include "../../definitions/MapDefinitions.h"

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
    void paint(EntityList& entities, Entity &player, EntityList& enemies);
    void init();
    void setMaxCameraDimensions(MapData data);
		//Deallocates memory
		~Map();
	private:
    Camera camera;
};

#endif
