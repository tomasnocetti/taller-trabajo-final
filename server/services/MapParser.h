#ifndef _MAP_PARSER_H_
#define _MAP_PARSER_H_

#if __APPLE__
#include <json/json.h>
#else
#include <jsoncpp/json/json.h>
#endif

#include <vector>
#include <string>
#include "../../DataDefinitions.h"

#define INVALID_MAP_FILE "Invalid Map file."

class MapParser {
  public:
    MapParser();
    MapParser(const MapParser&) = delete;
    MapParser& operator=(const MapParser&) = delete;
    MapParser&& operator=(MapParser&& other);
    ~MapParser();
    std::vector<struct TileLayerData>& getTileLayers();
    std::vector<struct ObjectLayerData>& getObjectLayers();
    MapData& getMapData();
  private:
    void loadMap(const std::string& path);
    void loadTileLayer(Json::Value& layer);
    void loadObjectLayer(Json::Value& layer);
    void loadTileSet(Json::Value& tileset);
    std::vector<struct ObjectLayerData> objectLayers;
    MapData mapData;
};

#endif
