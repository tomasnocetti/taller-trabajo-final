#include "Map.h"
#include <iostream>

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void Map::init() {
  this->camera.init(0, 0, MAIN_SCREEN_BASE_MAP_W, MAIN_SCREEN_BASE_MAP_H);
}

void Map::paint(EntityList& entities, Entity &player) {
  fit();
  this->camera.setX(player.getX() - MAIN_SCREEN_BASE_MAP_W / 2);
  this->camera.setY(player.getY() - MAIN_SCREEN_BASE_MAP_H / 2);
  for (auto& e : entities) e->paint(camera);
  player.paint(camera);
}

Map::~Map() {}
