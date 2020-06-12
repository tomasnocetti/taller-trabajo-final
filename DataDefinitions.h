#ifndef __DATADEF_H
#define __DATADEF_H

#include <string>
#include <vector>

struct MainPlayerData {};

struct TileSetData {
  int columns;
  int firstgid;
  int tilecount;
  std::string image;
};

struct TileLayerData {
  int id;
  std::string name;
  std::vector<size_t> data;
};

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

struct MapData {
  int height;
  int width;
  int tileheight;
  int tilewidth;
  std::vector<struct TileLayerData> layers;
  std::vector<struct TileSetData> tileSets;
};

#endif
