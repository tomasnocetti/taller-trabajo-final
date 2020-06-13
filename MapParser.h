#ifndef _MAP_PARSER_H_
#define _MAP_PARSER_H_

#include <jsoncpp/json/json.h>
#include <vector>
#include "DataDefinitions.h"

class MapParser {
  public:
    MapParser();
    MapParser(const MapParser&) = delete;
    MapParser& operator=(const MapParser&) = delete;
    MapParser&& operator=(MapParser&& other);
    ~MapParser();
    void loadMap(std::string src);
    std::vector<struct TileLayerData>& getTileLayers();
    std::vector<struct ObjectLayerData>& getObjectLayers();
    MapData& getMapData();
  private:
    void loadTileLayer(Json::Value& layer);
    void loadTileSet(Json::Value& tileset);
    void loadObjectLayer(Json::Value& layer);
    std::vector<struct ObjectLayerData> objectLayers;
    MapData mapData;
};

#endif
