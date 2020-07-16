#include "Map.h"

#define TILES_IN_MAP_ROW 17
#define TILES_IN_MAP_COL 13
#define TILE_SIZE 32
#define MAP_ROW_SIZE 150
#define TILES_PER_LAYER 22500

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

/*void Map::paint(Camera& camera,
  EntityList& entities,
  EntityList& drops,
  Entity &player,
  EntityList& enemies,
  EntityList& otherPlayers) {
  fit();

  for (auto& e : entities) e->paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());  //loopear por rango

  for(unsigned int i = 0; i <= TILES_IN_MAP_COL; i++){
    for(unsigned int j = 0; j <= TILES_IN_MAP_ROW; j++){
      entities[(camera.getX() / TILE_SIZE) + j + 
        (camera.getY() / TILE_SIZE * MAP_ROW_SIZE + i * MAP_ROW_SIZE)]->paint(
          camera, getScaleWidthFactor(), 
          getScaleHeightFactor());
    }
  }

  for (auto& e : drops) e->paint(camera, getScaleWidthFactor(), 
    getScaleHeightFactor());

  for (auto& e : enemies) e->paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());

  for (auto& e : otherPlayers) e->paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());
    
  player.paint(camera, getScaleWidthFactor(),
    getScaleHeightFactor());
}*/

void Map::paint(Camera& camera,
  EntityList& floor,
  EntityList& background,
  EntityList& drops,
  Entity &player,
  EntityList& enemies,
  EntityList& otherPlayers,
  EntityList& foreground) {
  fit();

  for(unsigned int i = 0; i <= TILES_IN_MAP_COL; i++){
    for(unsigned int j = 0; j <= TILES_IN_MAP_ROW; j++){
      floor[(camera.getX() / TILE_SIZE) + j + 
        (camera.getY() / TILE_SIZE * MAP_ROW_SIZE + i * MAP_ROW_SIZE)]->paint(
          camera, wScale, 
          hScale);
    }
  }

  /*for (auto& e : background) e->paint(camera, wScale,
    hScale);*/
  for(unsigned int i = 0; i <= TILES_IN_MAP_COL; i++){
    for(unsigned int j = 0; j <= TILES_IN_MAP_ROW; j++){
      background[(camera.getX() / TILE_SIZE) + j + 
        (camera.getY() / TILE_SIZE * MAP_ROW_SIZE + i * MAP_ROW_SIZE)]->paint(
          camera, wScale, 
          hScale);
    }
  }

  for (auto& e : drops) e->paint(camera, wScale, 
    hScale);

  for (auto& e : enemies) e->paint(camera, wScale,
    hScale);

  for (auto& e : otherPlayers) e->paint(camera, wScale,
    hScale);
    
  player.paint(camera, wScale,
    hScale);

  /*for (auto& e : foreground) e->paint(camera, wScale,
    hScale);*/
  for(unsigned int i = 0; i <= TILES_IN_MAP_COL; i++){
    for(unsigned int j = 0; j <= TILES_IN_MAP_ROW; j++){
      foreground[(camera.getX() / TILE_SIZE) + j + 
        (camera.getY() / TILE_SIZE * MAP_ROW_SIZE + i * MAP_ROW_SIZE)]->paint(
          camera, wScale, 
          hScale);
    }
  }

  for(unsigned int i = 0; i <= TILES_IN_MAP_COL; i++){
    for(unsigned int j = 0; j <= TILES_IN_MAP_ROW; j++){
      foreground[TILES_PER_LAYER + (camera.getX() / TILE_SIZE) + j + 
        (camera.getY() / TILE_SIZE * MAP_ROW_SIZE + i * MAP_ROW_SIZE)]->paint(
          camera, wScale, 
          hScale);
    }
  }
}

Map::~Map() {}
