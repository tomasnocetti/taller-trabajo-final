#include "Map.h"
#include <vector>

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h),
  // mapmanager("terrain", 1, 32)
  playerView((MAIN_SCREEN_BASE_MAP_W - MAIN_SCREEN_BASE_MAP_X) / 2,
    (MAIN_SCREEN_BASE_MAP_H - MAIN_SCREEN_BASE_MAP_Y) / 2, 
    std::move(window.createTexture())) {}

void Map::init() {
  // mapmanager.LoadMap(window, "assets/map/map.map", 25, 20);
  this->camera = { 0, 0,
      MAIN_SCREEN_BASE_MAP_W, MAIN_SCREEN_BASE_MAP_H };
  //playerView.paint(camera.x, camera.y);
}

void Map::paint(std::vector<std::unique_ptr<Entity>>& entities) {
  fit();
  //mapmanager.paint();
  this->camera.x = (playerView.getX()) - MAIN_SCREEN_BASE_MAP_W / 2;
  this->camera.y = (playerView.getY()) - MAIN_SCREEN_BASE_MAP_H / 2;
  if (camera.x < 0)
    camera.x = 0;
  if (camera.y < 0)
    camera.y = 0;
  if (camera.x > 58 * 16 - camera.w)
    camera.x = 58 * 16 - camera.w;
  if (camera.y > 47 * 16 - camera.h)
    camera.y = 47 * 16 - camera.h;
  for (auto& e : entities) e->paint(camera.x, camera.y);
  //background.paint(0, 0, &camera);
  playerView.paint(this->camera.x, this->camera.y);
}

void Map::handleEvent(const SDL_Event &e){
  switch (e.type){
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym){
        case SDLK_w:
          playerView.walk(0, -1);
        break;
        case SDLK_s:
          playerView.walk(0, 1);
        break;
        case SDLK_a:
          playerView.walk(-1, 0);
        break;
        case SDLK_d:
          playerView.walk(1, 0);
        break;
      }
    break;

    case SDL_KEYUP:
      switch (e.key.keysym.sym){
        case SDLK_w:
          playerView.stand(0, -1);
        break;
        case SDLK_s:
          playerView.stand(0, 1);
        break;
        case SDLK_a:
          playerView.stand(-1, 0);
        break;
        case SDLK_d:
          playerView.stand(1, 0);
        break;
      }
    break;
  }
}

Map::~Map() {}
