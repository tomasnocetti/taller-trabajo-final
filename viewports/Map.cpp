#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h)
  {}

void Map::paint(std::vector<std::unique_ptr<Entity>>& entities) {
  fit();
  for (auto& e : entities) e->paint();
}

void Map::init() {
}

Map::~Map() {}
