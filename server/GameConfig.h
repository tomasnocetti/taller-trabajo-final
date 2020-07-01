#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_


#if __APPLE__
#include <json/json.h>
#else
#include <jsoncpp/json/json.h>
#endif

#include <vector>
#include <map>
#include <string>
#include "definitions/Items.h"
#include "../DataDefinitions.h"

#define ERROR_MSG "No valid instance"
#define INVALID_CONFIG_FILE "Invalid config file"


struct TraderItem {
  int itemId;
  int value;
};

struct ChatMessages {
  std::string initialMsg;
  std::string damageRcvMsg;
  std::string enemyDodgedAttack;
  std::string attackDodged;
  std::string damageCaused;
  std::string insufficientFunds;
  std::string noInventorySpace;
  std::string invalidOption;
};

struct DropSizes{
  int height;
  int weight;
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
  size_t newbieLevel;
  size_t fairPlayLevel;
  std::map<int, std::unique_ptr<Item>> items;
  std::vector<TraderItem> traderItems;
  ChatMessages chatMessages;
  DropSizes dropSizes;
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
    GC() {}
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
