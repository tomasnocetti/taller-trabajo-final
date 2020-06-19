#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "EntityDefinitions.h"

#include "MapDefinitions.h"
#include <string>
#include <vector>

typedef enum {
  HUMAN,
  ELF,
  GNOME,
  DWARF
} PlayerRace;

typedef enum {
  MAGE,
  CLERIC,
  PALADIN,
  WARRIOR
} PlayerClass;

struct PlayerRootData {
  PlayerClass pclass;
  PlayerRace prace;
};

struct Inventory {
  std::string helmet;
};

struct HealthAndManaData {
  int totalHP;
  int currentHP;
  int totalMP;
  int currentMP;
};

struct MainPlayerData {
  PlayerRootData rootd;
  Inventory inventory;
  HealthAndManaData points;
  PositionData position;
  MovementData movement;
  size_t gold;
  size_t level;
};

struct OtherPlayersData {
  size_t id;
  PositionData otherPlayerPosition;
  PlayerRootData otherPlayerRoot;
};

struct PlayerGameModelData {
  MainPlayerData playerData;
  MapData map;
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
};

#endif
