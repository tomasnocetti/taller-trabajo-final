#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void Map::init() {
  this->camera.init(0, 0, MAIN_SCREEN_BASE_MAP_W, MAIN_SCREEN_BASE_MAP_H);
}

void Map::paint(EntityList& entities, Entity &player, EntityList& enemies) {
  fit();
  this->camera.setX(player.x - MAIN_SCREEN_BASE_MAP_W / 2);
  this->camera.setY(player.y - MAIN_SCREEN_BASE_MAP_H / 2);
  for (auto& e : entities) {
    e->paint(
      camera,
      getScaleWidthFactor(),
      getScaleHeightFactor());
  }
  for (auto& e : enemies) e->paint(camera);
  player.paint(camera);
}

Map::~Map() {}
