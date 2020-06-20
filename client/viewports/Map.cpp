#include "Map.h"

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void Map::init() {
  this->camera.init(0, 0, MAIN_SCREEN_BASE_MAP_W, MAIN_SCREEN_BASE_MAP_H);
}

void Map::setMaxCameraDimensions(MapData data){
	this->camera.setMaxDimensions(data.width * data.tilewidth, 
		data.height * data.tileheight);
}

void Map::paint(EntityList& entities, Entity &player, EntityList& enemies, 
  EntityList& otherPlayers) {
  fit();
  camera.setX(player.x - MAIN_SCREEN_BASE_MAP_W / 2);
  camera.setY(player.y - MAIN_SCREEN_BASE_MAP_H / 2);
  for (auto& e : entities) {
    e->paint(
      camera,
      getScaleWidthFactor(),
      getScaleHeightFactor());
  }
  for (auto& e : enemies) e->paint(camera, getScaleWidthFactor(),
      getScaleHeightFactor());
  for (auto& e : otherPlayers) e->paint(camera, getScaleWidthFactor(),
      getScaleHeightFactor());
  player.paint(camera, getScaleWidthFactor(),
      getScaleHeightFactor());
}

int Map::getCameraX() {
  return camera.getX() * getScaleWidthFactor();
}

int Map::getCameraY() {
  return camera.getY() * getScaleHeightFactor();
}

Map::~Map() {}
