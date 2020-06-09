#ifndef __DATADEF_H
#define __DATADEF_H

#include <string>

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

#endif
