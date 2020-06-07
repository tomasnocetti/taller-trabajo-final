#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h),
  // mapmanager("terrain", 1, 32)
  playerView((MAIN_SCREEN_BASE_MAP_W - MAIN_SCREEN_BASE_MAP_X) / 2,
    (MAIN_SCREEN_BASE_MAP_H - MAIN_SCREEN_BASE_MAP_Y) / 2, window)
  {}

void Map::paint() {
  fit();
  // mapmanager.paint();
  // texture.paint(0, 0, &camera);
  playerView.paint();
}

void Map::init() {
  // mapmanager.LoadMap(window, "assets/map/map.map", 25, 20);
}

void Map::handleEvent(const SDL_Event &e){
  switch(e.type){
    case SDL_KEYDOWN:
      switch(e.key.keysym.sym){
        case SDLK_w:
          playerView.moveY(-10);
        break;
        case SDLK_s:
          playerView.moveY(10);
        break;
        case SDLK_a:
          playerView.moveX(-10);
        break;
        case SDLK_d:
          playerView.moveX(10);
        break;
      }
    break;
  }
}

Map::~Map() {}
