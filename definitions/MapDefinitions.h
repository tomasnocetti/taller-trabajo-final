
#ifndef __MAPDEF_H
#define __MAPDEF_H

#include <string>
#include <vector>
#include <msgpack.hpp>

#define MARGIN_LAYER "margenes"
#define SPIDER_SPAWN_POINTS "spider-spawn"
#define SKELETON_SPAWN_POINTS "skeleton-spawn"
#define GOBLIN_SPAWN_POINTS "goblin-spawn"
#define CITY_LAYER "ciudad"

#define MAIN_SCREEN_BASE_MAP_X 11
#define MAIN_SCREEN_BASE_MAP_Y 154
#define MAIN_SCREEN_BASE_MAP_W 542
#define MAIN_SCREEN_BASE_MAP_H 413

#define CHAT_BASE_X 11
#define CHAT_BASE_Y 15
#define CHAT_BASE_W 542
#define CHAT_BASE_H 180
#define CHAT_BUTTON_X 57
#define CHAT_BUTTON_Y 129
#define CHAT_BUTTON_W 58
#define CHAT_BUTTON_H 15
#define CHAT_INPUT_X 71
#define CHAT_INPUT_Y 116
#define CHAT_INPUT_W 475
#define CHAT_INPUT_H 14

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
