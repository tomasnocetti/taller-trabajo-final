#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void Map::paint(Camera& camera,
  EntityList& entities,
  EntityList& drops,
  Entity &player,
  EntityList& enemies,
  EntityList& otherPlayers) {
  fit();

  for (auto& e : entities) e->paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());

  for (auto& e : drops) e->paint(camera, getScaleWidthFactor(), 
    getScaleHeightFactor());

  for (auto& e : enemies) e->paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());

  for (auto& e : otherPlayers) e->paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());
    
  player.paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());
}

Map::~Map() {}
