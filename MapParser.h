#pragma once

#include <json/json.h>
#include <memory>
#include <vector>
#include "DataDefinitions.h"

using TileLayers = std::vector<std::unique_ptr<TileLayerData>>;

class MapParser {
  public:
    MapParser();
    MapParser(const MapParser&) = delete;
    MapParser& operator=(const MapParser&) = delete;
    MapParser&& operator=(MapParser&& other);
    ~MapParser();
    void loadMap(std::string src);
    TileLayers& getTileLayers();
  private:
    void loadTileLayer(Json::Value& layer);
    void loadTileSet(Json::Value& tileset);
    TileLayers tilelayers;
    std::vector<std::unique_ptr<TileSetData>> tilesets;
    int height;
    int width;
    int tileheight;
    int tilewidth;
};
