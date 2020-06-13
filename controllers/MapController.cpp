#include "MapController.h"
#include "../MapParser.h"
#include "../DataDefinitions.h"
#include "../entities/TileEntity.h"
#include <iostream>
#include <algorithm>

MapController::~MapController() {
  for (auto &i : tiles) {
    i.reset();
  }
}

void MapController::init(SdlWindow& window){
  // THIS WILL GO SERVER SIDE
  // ------
  MapParser m;
  m.loadMap("assets/map/island2.json");
  MapData& map = m.getMapData();
  for (unsigned int i = 0; i < map.tileSets.size(); i++){
    textures.push_back(new LTexture(window.createTexture()));
    textures[i]->loadFromFile("assets/map/" + map.tileSets[i].image);
  }

  std::vector<struct TileLayerData>& layers = m.getTileLayers();
  std::vector<struct ObjectLayerData>& objectl = m.getObjectLayers();

  for (unsigned int i = 0; i < objectl.size(); i++){
    for (unsigned int j = 0; j < objectl[i].objects.size(); j++){
      std::cout << objectl[i].objects[j].x << std::endl;
      std::cout << objectl[i].objects[j].y << std::endl;
      std::cout << objectl[i].objects[j].width << std::endl;
      std::cout << objectl[i].objects[j].height << std::endl;
    }
  }

  std::for_each(layers.begin(), layers.end(), 
    [this, &map](struct TileLayerData& layer){
    int tileSize = map.tilewidth;
    int mapSizeColumns = map.width;
    for (unsigned int y = 0; y < layer.data.size(); y++) {
      int tilegid = layer.data[y];
      unsigned int firstgid, tileSetColumns, j;
      if (tilegid > 0){ 
        for (j = 0; j < map.tileSets.size(); j++){
          if (map.tileSets[j].firstgid > tilegid){
            firstgid = map.tileSets[j - 1].firstgid;
            tileSetColumns = map.tileSets[j - 1].columns;
            j--;
            break;
          }
          if (j == map.tileSets.size() - 1){
            firstgid = map.tileSets[j].firstgid;
            tileSetColumns = map.tileSets[j].columns;
            break;
          }
        }
        tilegid -= firstgid;
        tiles.emplace_back(
        new TileEntity(
          textures[j],
          (tilegid % tileSetColumns) * tileSize,
          (tilegid / tileSetColumns) * tileSize,
          (y % mapSizeColumns) * tileSize,
          (y / mapSizeColumns) * tileSize,
          tileSize,
          mapScale,
          texID));
      }
    }
  });
}

EntityList& MapController::getEntities() {
  return tiles;
}
