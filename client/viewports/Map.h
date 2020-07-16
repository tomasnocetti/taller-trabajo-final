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
    /*void paint(
      Camera& camera,
      EntityList& entities,
      EntityList& drops,
      Entity &player,
      EntityList& enemies,
      EntityList& otherPlayers);*/
    void paint(
      Camera& camera,
      EntityList& floor,
      EntityList& background,
      EntityList& drops,
      Entity &player,
      EntityList& enemies,
      EntityList& otherPlayers,
      EntityList& foreground);
		//Deallocates memory
		~Map();
	private:
};

#endif
