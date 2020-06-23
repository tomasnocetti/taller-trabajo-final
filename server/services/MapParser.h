#ifndef _MAP_PARSER_H_
#define _MAP_PARSER_H_

//#include <json/json.h>
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include "../../DataDefinitions.h"


class MapParser {
  public:
    MapParser();
    MapParser(const MapParser&) = delete;
    MapParser& operator=(const MapParser&) = delete;
    MapParser&& operator=(MapParser&& other);
    ~MapParser();
    void loadMap(char* src);
    std::vector<struct TileLayerData>& getTileLayers();
    std::vector<struct ObjectLayerData>& getObjectLayers();
    MapData& getMapData();
  private:
    void loadTileLayer(Json::Value& layer);
    void loadObjectLayer(Json::Value& layer);
    void loadTileSet(Json::Value& tileset);
    std::vector<struct ObjectLayerData> objectLayers;
    MapData mapData;
};

#endif
