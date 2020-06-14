#include "MapController.h"
#include "../MapParser.h"
#include "../entities/TileEntity.h"
#include "../../DataDefinitions.h"
#include <iostream>
#include <algorithm>
//#include <fstream>
//#include <vector>

MapController::MapController(ClientProxy& model) : model(model) {}

MapController::~MapController() {
  for (auto &i : tiles) {
    i.reset();
  }
}

void MapController::init(SdlWindow& window){
  MapData map = model.getMapData();
  // THIS WILL GO SERVER SIDE
  // ------
 // MapParser m;
  //m.loadMap("client/assets/map/pindonga2.json");
  //MapData& map = m.getMapData();

  for (unsigned int i = 0; i < map.tileSets.size(); i++){
    textures.push_back(new LTexture(window.createTexture()));
    textures[i]->loadFromFile("client/assets/map/" + map.tileSets[i].image);
  }

  std::vector<struct TileLayerData>& layers = map.layers;

  std::for_each(layers.begin(), layers.end(), [this, &map]
    (struct TileLayerData& layer){
    int tileSize = map.tilewidth;
    int mapSizeColumns = map.width;
    for (unsigned int y = 0; y < layer.data.size(); y++) {
      int tilegid = layer.data[y];
      unsigned int firstgid = 0, tileSetColumns = 0, j;
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
