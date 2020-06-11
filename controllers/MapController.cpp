#include "MapController.h"
#include "../MapParser.h"
#include "../DataDefinitions.h"
#include <iostream>
#include <algorithm>
#include <fstream>

MapController::~MapController() {
  for (auto &i : tiles) {
    i.reset();
  }
}

void MapController::init(SdlWindow& window){
  // THIS WILL GO SERVER SIDE
  // ------
  /*MapParser m;
  m.loadMap("assets/map/island2.json");
  TileSets& tilesets = m.getTileSets();
  for(unsigned int i = 0; i < tilesets.size(); i++){
    textures[i] = new LTexture(window.createTexture());
    textures[i]->loadFromFile("assets/map/" + tilesets[i]->image);
  }
  //textures[0] = new LTexture(window.createTexture());
  //textures[0]->loadFromFile("assets/map/beach_tileset.png");

  TileLayers& layers = m.getTileLayers();
  MapData& map = m.getMapData();

  std::for_each(layers.begin(), layers.end(), [this, &map](std::unique_ptr<TileLayerData>& layer){
    int tileSize = map.tilewidth;
    int tileSetColumns = 36;
    int mapSizeColumns = map.width;
    for (unsigned int y = 0; y < layer->data.size(); y++) {
      int tilegid = layer->data[y] - 1;
      //std::cout << tilegid << std::endl;
      tiles.emplace_back(
        new TileEntity(
          textures[0],
          (tilegid % tileSetColumns) * tileSize,
          (tilegid / tileSetColumns) * tileSize,
          (y % mapSizeColumns) * tileSize,
          (y / mapSizeColumns) * tileSize,
          tileSize,
          mapScale,
          texID)
      );
    }
  });*/

  MapParser m;
  m.loadMap("assets/map/island2.json");
  MapData& map = m.getMapData();
  for(unsigned int i = 0; i < map.tilesetImage.size(); i++){
    textures[i] = new LTexture(window.createTexture());
    textures[i]->loadFromFile("assets/map/" + map.tilesetImage[i]);
  }

  TileLayers& layers = m.getTileLayers();

  std::for_each(layers.begin(), layers.end(), [this, &map](std::unique_ptr<TileLayerData>& layer){
    int tileSize = map.tilewidth;
    int mapSizeColumns = map.width;
    for (unsigned int y = 0; y < layer->data.size(); y++) {
      int tilegid = layer->data[y];
      unsigned int firstgid, tileSetColumns, j;
      if(tilegid > 0){    //preguntar
        for(j = 0; j < map.tilesetFirstgid.size(); j++){
          if(map.tilesetFirstgid[j] > tilegid){
            firstgid = map.tilesetFirstgid[j - 1];
            tileSetColumns = map.tilesetColumns[j - 1];
            j--;
            break;
          }
          if(j == map.tilesetFirstgid.size() - 1){
            firstgid = map.tilesetFirstgid[j];
            tileSetColumns = map.tilesetColumns[j];
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
          texID)
        );
      }
    }
  });
}

EntityList& MapController::getEntities() {
  return tiles;
}
