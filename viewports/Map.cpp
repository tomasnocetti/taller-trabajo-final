#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void Map::init() {
  this->camera = { 0, 0,
      MAIN_SCREEN_BASE_MAP_W, MAIN_SCREEN_BASE_MAP_H };
}

void Map::paint(EntityList& entities, Entity &player) {
  fit();
  this->camera.x = player.getX() - MAIN_SCREEN_BASE_MAP_W / 2;
  this->camera.y = player.getY() - MAIN_SCREEN_BASE_MAP_H / 2;
  if (camera.x < 0)
    camera.x = 0;
  if (camera.y < 0)
    camera.y = 0;
  if (camera.x > 640 - camera.w)
    camera.x = 640 - camera.w;
  if (camera.y > 640 - camera.h)
    camera.y = 640 - camera.h;
  for (auto& e : entities) e->paint(camera.x, camera.y);
  player.paint(camera.x, camera.y);
}

Map::~Map() {}
