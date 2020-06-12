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

struct MapData {
  int height;
  int width;
  int tileheight;
  int tilewidth;
  std::vector<int> tilesetColumns;
  std::vector<int> tilesetFirstgid;
  std::vector<int> tilesetTileCount;
  std::vector<std::string> tilesetImage;
};

#endif
