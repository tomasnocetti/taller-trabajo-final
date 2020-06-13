#include "MapParser.h"
#include <fstream>
#include <algorithm>

MapParser::MapParser() {}
MapParser::~MapParser() {
}

void MapParser::loadMap(std::string src) {
  Json::Value root;

  std::ifstream file(src, std::ifstream::binary);
  file >> root;

  mapData.height = root["height"].asInt();
  mapData.width = root["width"].asInt();
  mapData.tileheight = root["tileheight"].asInt();
  mapData.tilewidth = root["tilewidth"].asInt();

  const Json::Value layers = root["layers"];
  std::for_each(
    layers.begin(),
    layers.end(),
    [this](Json::Value layer){
      std::string t(layer["type"].asString());
      if (t == "tilelayer") loadTileLayer(layer);
      if (t == "objectgroup") loadObjectLayer(layer);
    });

  const Json::Value tilesets = root["tilesets"];

  std::for_each(
    tilesets.begin(),
    tilesets.end(),
    [this](Json::Value tileset){
      loadTileSet(tileset);
    });
}

void MapParser::loadTileLayer(Json::Value& layer) {
  TileLayerData layerData;

  layerData.id = layer["id"].asInt();
  layerData.name = layer["name"].asString();
  layerData.data.reserve(layer["data"].size());

  std::for_each(
    layer["data"].begin(),
    layer["data"].end(),
    [&layerData](Json::Value gid) {
      layerData.data.emplace_back(gid.asUInt());
    });

  mapData.layers.push_back(layerData);
}

void MapParser::loadObjectLayer(Json::Value& layer) {
  ObjectLayerData layerData;

  layerData.id = layer["id"].asInt();
  layerData.name = layer["name"].asString();

  std::for_each(
    layer["objects"].begin(),
    layer["objects"].end(),
    [&layerData](Json::Value object) {
      ObjectData objectData;
      objectData.x = object["x"].asInt();
      objectData.y = object["y"].asInt();
      objectData.width = object["width"].asInt();
      objectData.height = object["height"].asInt();

      layerData.objects.push_back(objectData);
    });

  objectLayers.push_back(layerData);
}

void MapParser::loadTileSet(Json::Value& tileset) {
  TileSetData tileSetData;

  tileSetData.columns = tileset["columns"].asUInt();
  tileSetData.firstgid = tileset["firstgid"].asUInt();
  tileSetData.tilecount = tileset["tilecount"].asUInt();
  tileSetData.image = tileset["image"].asString();

  mapData.tileSets.push_back(tileSetData);
}

std::vector<struct TileLayerData>& MapParser::getTileLayers() {
  return mapData.layers;
}

std::vector<struct ObjectLayerData>& MapParser::getObjectLayers() {
  return objectLayers;
}

MapData& MapParser::getMapData() {
  return mapData;
}
