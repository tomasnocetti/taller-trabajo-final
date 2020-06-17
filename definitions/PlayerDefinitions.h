#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "EntityDefinitions.h"
#include <string>

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

struct Inventory{
  std::string helmet;
};

struct HealthData {
  int totalPoints;
  int currentPoints;
};

struct MainPlayerData {
  MovementData movement;
  PlayerRootData rootd;
  PositionData position;
  uint32_t manaPoints;
  uint32_t gold;
  uint32_t level;
};

#endif
