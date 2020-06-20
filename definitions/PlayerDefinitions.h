#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "EntityDefinitions.h"
#include "NPCDefinitions.h"
#include "MapDefinitions.h"
#include <string>
#include <vector>

typedef enum {
  HUMAN,
  ELF,
  GNOME,
  DWARF
} PlayerRace;

MSGPACK_ADD_ENUM(PlayerRace)

typedef enum {
  MAGE,
  CLERIC,
  PALADIN,
  WARRIOR
} PlayerClass;

MSGPACK_ADD_ENUM(PlayerClass)

struct PlayerRootData {
  PlayerClass pclass;
  PlayerRace prace;
  MSGPACK_DEFINE(pclass, prace)
};

struct Inventory {
  std::string helmet;
  MSGPACK_DEFINE(helmet)
};

struct HealthAndManaData {
  int totalHP;
  int currentHP;
  int totalMP;
  int currentMP;
  MSGPACK_DEFINE(totalHP, currentHP, totalMP, currentMP)
};

struct MainPlayerData {
  PlayerRootData rootd;
  Inventory inventory;
  HealthAndManaData points;
  PositionData position;
  MovementData movement;
  size_t gold;
  size_t level;
  MSGPACK_DEFINE(rootd, inventory, points, position, movement, gold, level)
};

struct OtherPlayersData {
  size_t id;
  PositionData otherPlayerPosition;
  PlayerRootData otherPlayerRoot;
  MSGPACK_DEFINE(id, otherPlayerPosition, otherPlayerRoot)
};

struct PlayerGameModelData {
  MainPlayerData playerData;
  MapData map;
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
  MSGPACK_DEFINE(playerData, map, npcs, otherPlayers)
};

#endif
