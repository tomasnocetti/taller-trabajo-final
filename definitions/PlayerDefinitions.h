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

struct HealthAndManaData {
  int totalHP;
  int currentHP;
  int totalMP;
  int currentMP;
};

struct MainPlayerData {
  PlayerRootData rootd;
  PositionData position;
  HealthAndManaData points;
  int speed; 
  uint32_t gold;
  uint32_t level;
};

#endif
