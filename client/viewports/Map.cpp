#include "Map.h"

#define TILES_IN_MAP_ROW 17
#define TILES_IN_MAP_COL 13
#define TILE_SIZE 32
#define MAP_ROW_SIZE 150
#define TILES_PER_LAYER 22500

Map::Map(SdlWindow& window, int x, int y, int w, int h) :
  SdlViewport(window, x, y, w, h) {}

void Map::paint(Camera& camera,
  EntityList& background,
  EntityList& drops,
  Entity &player,
  EntityList& enemies,
  EntityList& otherPlayers,
  EntityList& foreground) {
  fit();

  paintLayer(background, camera, 0);
  paintLayer(background, camera, TILES_PER_LAYER);

  for (auto& e : drops) e->paint(camera, wScale, 
    hScale);

  for (auto& e : enemies) e->paint(camera, wScale,
    hScale);

  for (auto& e : otherPlayers) e->paint(camera, wScale,
    hScale);
    
  player.paint(camera, wScale,
    hScale);

  paintLayer(foreground, camera, 0);
  paintLayer(foreground, camera, TILES_PER_LAYER);
}

void Map::paintLayer(EntityList& layer, const Camera& camera, int offset){
  std::shared_ptr<Entity> tile;
  for(unsigned int i = 0; i <= TILES_IN_MAP_COL; i++){
    for(unsigned int j = 0; j <= TILES_IN_MAP_ROW; j++){
      tile = layer[offset + (camera.getX() / TILE_SIZE) + j + 
        (camera.getY() / TILE_SIZE * MAP_ROW_SIZE + i * MAP_ROW_SIZE)];
      if (tile != nullptr)
       tile->paint(camera, wScale, hScale);
    }
  }
}

Map::~Map() {}
