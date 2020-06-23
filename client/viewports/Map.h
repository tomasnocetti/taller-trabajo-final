#ifndef _MAPV_H_
#define _MAPV_H_

#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../view/Camera.h"
#include "../entities/Entity.h"
#include "../../definitions/MapDefinitions.h"

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
    void paint(EntityList& entities, Entity &player, EntityList& enemies, 
      EntityList& otherPlayers);
    void init();
    void setMaxCameraDimensions(MapData data);
    int getCameraX();
    int getCameraY();
		//Deallocates memory
		~Map();
	private:
    Camera camera;
};

#endif
