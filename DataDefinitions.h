#ifndef __DATADEF_H
#define __DATADEF_H

#include <string>
#include <vector>
#include <msgpack.hpp>

struct PositionData {
  int x;
  int y;
  int w;
  int h;
};

struct HealthData {
  int totalPoints;
  int currentPoints;
};

typedef struct EntityData {
  PositionData position;
  bool isDead;
  uint32_t lifePoints;
} EntityDataT;

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

typedef struct ParamData {
  std::string value;
  MSGPACK_DEFINE(value)
} ParamDataT;

typedef enum {
  MOVE,
  BUY,
  DEPOSIT_GOLD,
  DEPOSIT_ITEM,
  ATTACK,
  CLOSE_SERVER
} ActionTypeT;

typedef struct InstructionData {
  size_t playerId;
  ActionTypeT action;
  std::vector<ParamData> params;
  //MSGPACK_DEFINE(playerId, params, action)
} IntructionDataT;

typedef struct Inventory{
  std::string helmet;
} InventoryT;

typedef struct PlayerData{
  uint32_t manaPoints;
  uint32_t gold;
  std::string type;
  uint32_t accountNumber;
  uint32_t level;
  EntityDataT data; 
  InventoryT inventory;
} PlayerDataT;

typedef struct GameModel{
  std::string action;
} GameModelT;

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
