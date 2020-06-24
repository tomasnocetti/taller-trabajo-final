#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "NPCDefinitions.h"
#include "MapDefinitions.h"
#include "EquipmentDefinitions.h"
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

struct LevelExperienceAndSkillsData {
  size_t level;
  size_t currentExperience;
  size_t maxLevelExperience;
  size_t strength;
  size_t agility;
  size_t inteligence;
  MSGPACK_DEFINE(level, currentExperience, maxLevelExperience, 
    strength, agility, inteligence)
};

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
  std::string nick;
  size_t id;
  size_t gold;
  LevelExperienceAndSkillsData levelExperienceSkills;
  PlayerRootData rootd;
  Inventory inventory;
  HealthAndManaData points;
  PositionData position;
  MovementData movement;
  EquipmentData equipment;
  MSGPACK_DEFINE(nick, id, gold, levelExperienceSkills, rootd, inventory, 
    points, position, movement, equipment)
};

struct OtherPlayersData {
  size_t id;
  PositionData position;
  MovementData movement;
  PlayerRootData rootd;
  MSGPACK_DEFINE(id, position, rootd)
};

struct PlayerGameModelData {
  MainPlayerData playerData;
  MapData map;
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
  MSGPACK_DEFINE(playerData, map, npcs, otherPlayers)
};

#endif
