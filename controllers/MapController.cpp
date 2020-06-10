#include "MapController.h"
#include "../MapParser.h"
#include "../DataDefinitions.h"
#include "../view/PlayerView.h"
#include <iostream>
#include <algorithm>
#include <fstream>

MapController::~MapController() {
  for (auto &i : tiles) {
    i.reset();
  }
}

void MapController::init(SdlWindow& window){
  textures[0] = new LTexture(window.createTexture());
  textures[0]->loadFromFile("assets/map/beach_tileset.png");
  // THIS WILL GO SERVER SIDE
  MapParser m;
  m.loadMap("assets/map/island2.json");
  // ------

  TileLayers& layers = m.getTileLayers();

  std::for_each(layers.begin(), layers.end(), 
  [this](std::unique_ptr<TileLayerData>& layer){
    int tileSize = 16;
    int tileSetColumns = 36;
    int mapSizeColumns = 58;
    for (int y = 0; y < layer->data.size(); y++) {
      int tilegid = layer->data[y] - 1;
      tiles.emplace_back(
        new TileEntity(
          textures[0],
          (tilegid % tileSetColumns) * tileSize,
          (tilegid / tileSetColumns) * tileSize,
          (y % mapSizeColumns) * tileSize,
          (y /mapSizeColumns) * tileSize,
          tileSize, 
          mapScale, 
          texID));
    }
  });
}

EntityList& MapController::getEntities() {
  return tiles;
}
