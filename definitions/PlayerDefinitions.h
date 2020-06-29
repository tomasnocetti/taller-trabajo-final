#ifndef __PLAYERDEF_H
#define __PLAYERDEF_H

#include "NPCDefinitions.h"
#include "MapDefinitions.h"
#include "EntityDefinitions.h"
#include "EquipmentDefinitions.h"
#include <string>
#include <vector>

#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 48

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

struct ResurrectionData{
  std::chrono::system_clock::time_point timeToResurrection;
  bool resurrect;
  PositionData position;
};

struct InventoryElementData{
  size_t amount;
  bool isEquiped;
  Equipable equipableType;
  char enumPosition;
  MSGPACK_DEFINE(amount, isEquiped, equipableType, enumPosition)
};

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
  size_t minLevelExperience;
  MSGPACK_DEFINE(currentExperience, maxLevelExperience, minLevelExperience)
};

struct PlayerRootData {
  PlayerClass pclass;
  PlayerRace prace;
  MSGPACK_DEFINE(pclass, prace)
};

struct MainPlayerData {
  std::string nick;
  size_t id;
  size_t gold;
  size_t level;
  ExperienceData experience;
  SkillsData skills;
  PlayerRootData rootd;
  std::vector<InventoryElementData> inventory;
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
  size_t otherPlayerHealth;
  ResurrectionData resurrection;
  MSGPACK_DEFINE(id, position, rootd, equipment, otherPlayerHealth)
};

struct PlayerGameModelData {
  MainPlayerData playerData;
  //MapData map;
  std::vector<EnemyData> npcs;
  std::vector<OtherPlayersData> otherPlayers;
  MSGPACK_DEFINE(playerData, npcs, otherPlayers)
};

#endif
