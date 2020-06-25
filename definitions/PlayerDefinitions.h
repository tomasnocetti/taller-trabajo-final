#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "NPCDefinitions.h"
#include "MapDefinitions.h"
#include "EntityDefinitions.h"
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

struct SkillsData {
  size_t strength;
  size_t agility;
  size_t inteligence;
  size_t classRecovery;
  size_t classMeditation;
  size_t raceRecovery;
  size_t raceMeditation;
  size_t classMana;
  size_t classHealth;
  size_t raceMana;
  size_t raceHealth;
  size_t classConstitution;
  MSGPACK_DEFINE(strength, agility, inteligence, classRecovery, 
    classMeditation, raceRecovery, raceMeditation, classMana, classHealth,
    raceMana, raceHealth, classConstitution)
};

struct ExperienceData{
  size_t currentExperience;
  size_t maxLevelExperience;
  MSGPACK_DEFINE(currentExperience, maxLevelExperience)
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

struct MainPlayerData {
  std::string nick;
  size_t id;
  size_t gold;
  size_t level;
  ExperienceData experience;
  SkillsData skills;
  PlayerRootData rootd;
  Inventory inventory;
  HealthAndManaData points;
  PositionData position;
  MovementData movement;
  EquipmentData equipment;
  MSGPACK_DEFINE(nick, id, gold, level, experience, skills, rootd, inventory, 
    points, position, movement, equipment)
};

struct OtherPlayersData {
  size_t id;
  PositionData position;
  MovementData movement;
  PlayerRootData rootd;
  EquipmentData equipment;
  MSGPACK_DEFINE(id, position, rootd, equipment)
};

struct PlayerGameModelData {
  MainPlayerData playerData;
  //MapData map;
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
  MSGPACK_DEFINE(playerData, npcs, otherPlayers)
};

#endif
