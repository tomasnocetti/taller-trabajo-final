#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_

#if __APPLE__
#include <json/json.h>
#elif
#include <jsoncpp/json/json.h>
#endif

#include <vector>
#include <map>
#include <string>
#include "../DataDefinitions.h"

#define ERROR_MSG "No valid instance"
#define INVALID_CONFIG_FILE "Invalid config file"

struct Item {
  int id;
  Equipable type;
  std::string name;
};

struct TraderItem {
  int itemId;
  int value;
};

struct GlobalConfig {
  int attackZoneWidth;
  int attackZoneHeight;
  int attackNpcZoneWidth;
  int attackNpcZoneHeight;
  int maxRangeZone;
  int offsetToRespawn;
  int minDistanceNpc;
  int minDistanceToAttackPlayer;
  int speed;
  int speedNpc;
  int respawnTimeNpc;
  int attackInterval;
  double npcRandomDrop;
  int npcInitHealthPoints;
  size_t npcInitSkills;
  int playerInitialLevel;
  std::map<int, Item> items;
  std::vector<TraderItem> traderItems;
};

struct RaceSkillsData {
  size_t recovery;
  size_t mana;
  size_t meditation;
  size_t health;
  size_t constitution;
  size_t inteligence;
  size_t strength;
  size_t agility;
};

class GC {
  public:
    GC() {};
    GC(const GC&) = delete;
    GC& operator=(const GC&) = delete;
    GC&& operator=(GC&& other) = delete;
    static void load(const char* src);
    static const GlobalConfig& get();

  private:
    GlobalConfig g;
    std::map<char, RaceSkillsData> raceData;
    static GC* instance;
};

#endif
