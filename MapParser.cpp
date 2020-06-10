#include "MapParser.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

MapParser::MapParser() {}
MapParser::~MapParser() {
}

void MapParser::loadMap(std::string src) {
  Json::Value root;

  std::ifstream file(src, std::ifstream::binary);
  file >> root;
  height = root["height"].asInt();
  width = root["width"].asInt();
  tileheight = root["tileheight"].asInt();
  tilewidth = root["tilewidth"].asInt();

  const Json::Value layers = root["layers"];
  std::for_each(
    layers.begin(),
    layers.end(),
    [this](Json::Value layer){
      std::string t(layer["type"].asString());
      if (t == "tilelayer") loadTileLayer(layer);
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
  std::unique_ptr<TileLayerData> l(new TileLayerData);

  l->id = layer["id"].asInt();
  l->name = layer["name"].asString();
  l->data.reserve(layer["data"].size());

  std::for_each(
    layer["data"].begin(),
    layer["data"].end(),
    [&l](Json::Value gid) {
      l->data.emplace_back(gid.asUInt());
    });

  tilelayers.push_back(std::move(l));
}

void MapParser::loadTileSet(Json::Value& tileset) {
  std::unique_ptr<TileSetData> s(new TileSetData);

  s->columns = tileset["columns"].asUInt();
  s->firstgid = tileset["firstgid"].asUInt();
  s->tilecount = tileset["tilecount"].asUInt();
  s->image = tileset["image"].asString();
  tilesets.push_back(std::move(s));
}

TileLayers& MapParser::getTileLayers() {
  return tilelayers;
}
