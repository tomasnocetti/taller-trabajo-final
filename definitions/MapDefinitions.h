
#ifndef __MAPDEF_H
#define __MAPDEF_H

#include <string>
#include <vector>
#include <msgpack.hpp>

#define MARGIN_LAYER "margenes"

#define MAIN_SCREEN_BASE_MAP_X 11
#define MAIN_SCREEN_BASE_MAP_Y 154
#define MAIN_SCREEN_BASE_MAP_W 542
#define MAIN_SCREEN_BASE_MAP_H 413

struct ObjectLayerData {
  int id;
  std::string name;
  std::vector<struct ObjectData> objects;
};

struct ObjectData {
  int x;
  int y;
  int width;
  int height;
};

struct TileSetData {
  int columns;
  int firstgid;
  int tilecount;
  std::string image;
  MSGPACK_DEFINE(columns, firstgid, tilecount, image)
};

struct TileLayerData {
  int id;
  std::string name;
  std::vector<size_t> data;
  MSGPACK_DEFINE(id, name, data)
};

struct MapData {
  int height;
  int width;
  int tileheight;
  int tilewidth;
  std::vector<struct TileLayerData> layers;
  std::vector<struct TileSetData> tileSets;
  MSGPACK_DEFINE(height, width, tileheight, tilewidth, layers, tileSets)
};

#endif
