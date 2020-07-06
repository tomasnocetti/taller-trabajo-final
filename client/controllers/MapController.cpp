#include "MapController.h"
#include "../entities/TileEntity.h"
#include "../entities/DropEntity.h"
#include "../../definitions/MapDefinitions.h"
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
  const MapData& map = model.getMapData();

  for (unsigned int i = 0; i < map.tileSets.size(); i++){
    std::string src = "/var/argentum/assets/map/" + map.tileSets[i].image;
    manager.addTexture(map.tileSets[i].image, src.data());
  }

  std::vector<struct TileLayerData> layers = map.layers;

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
  if (!mapIsSet && model.isMapSet()) init();
}

void MapController::updateDrops() {
  const std::vector<DropItemData>& items = model.getDrops();
  
  drops.clear();
  for (unsigned int i = 0; i < items.size(); i++)
    generateDrop(items[i]);
}

void MapController::generateDrop(DropItemData item) {
  LTexture* texture = manager.getTexture(
    "item_" + std::to_string(item.id));
  std::shared_ptr<DropEntity> drop(new DropEntity(
    texture, item.position.x, item.position.y, 
    item.position.w, item.position.h));

  drops.emplace_back(drop);
}

EntityList& MapController::getEntities() {
  return tiles;
}

EntityList& MapController::getDrops() {
  return drops;
}
