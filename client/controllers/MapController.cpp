#include "MapController.h"
#include "../entities/TileEntity.h"
#include "../../DataDefinitions.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

MapController::MapController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

MapController::~MapController() {
  for (auto &i : tiles) {
    i.reset();
  }
}

void MapController::init(){
  MapData map = model.getMapData();

  for (unsigned int i = 0; i < map.tileSets.size(); i++){
    std::string src = "client/assets/map/" + map.tileSets[i].image;
    manager.addTexture(map.tileSets[i].image, src.data());
  }

  std::vector<struct TileLayerData>& layers = map.layers;

  std::for_each(layers.begin(), layers.end(), [this, &map]
    (struct TileLayerData& layer){
    int tileSize = map.tilewidth;
    int mapSizeColumns = map.width;
    for (unsigned int y = 0; y < layer.data.size(); y++) {
      int tilegid = layer.data[y];
      unsigned int firstgid = 0, tileSetColumns = 0, j;
      std::string image;
      if (tilegid <= 0) continue;

      for (j = 0; j < map.tileSets.size(); j++){
        if (map.tileSets[j].firstgid > tilegid){
          firstgid = map.tileSets[j - 1].firstgid;
          tileSetColumns = map.tileSets[j - 1].columns;
          image = map.tileSets[j - 1].image;
          j--;
          break;
        }
        if (j == map.tileSets.size() - 1){
          firstgid = map.tileSets[j].firstgid;
          tileSetColumns = map.tileSets[j].columns;
          image = map.tileSets[j].image;
          break;
        }
      }
      tilegid -= firstgid;
      tiles.emplace_back(
        new TileEntity(
          manager.getTexture(image),
          (tilegid % tileSetColumns) * tileSize,
          (tilegid / tileSetColumns) * tileSize,
          (y % mapSizeColumns) * tileSize,
          (y / mapSizeColumns) * tileSize,
          tileSize,
          mapScale,
          texID));
    }
  });
  mapIsSet = true;
}

void MapController::update(){ 
  if(!mapIsSet && model.isMapSet()) init();
}

EntityList& MapController::getEntities() {
  return tiles;
}
