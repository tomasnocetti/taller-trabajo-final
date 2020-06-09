#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h)
  // mapmanager("terrain", 1, 32)
  {}

void Map::paint() {
  fit();
  // mapmanager.paint();
  // texture.paint(0, 0, &camera);
}

void Map::init() {
  // mapmanager.LoadMap(window, "assets/map/map.map", 25, 20);
}

Map::~Map() {}
