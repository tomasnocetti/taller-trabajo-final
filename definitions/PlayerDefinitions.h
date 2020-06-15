#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "EntityDefinitions.h"
#include "MapDefinitions.h"

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

struct HealthData {
  int totalPoints;
  int currentPoints;
};

struct MainPlayerData {
  PlayerRootData root;
  Inventory inventory;
  HealthData health;
  PositionData position;
  size_t manaPoints;
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
  std::vector<EnemyData> npcs;
  MapData map;
  std::vector<OtherPlayersData> otherPlayers;
};

#endif
