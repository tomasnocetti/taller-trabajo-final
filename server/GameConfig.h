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
  std::string meditating;
  std::string stopMeditating;
  std::string inventoryIsFull; 
};

struct DropSizes{
  int height;
  int weight;
};

struct RaceSkillsData {
  int recovery;
  int mana;
  int meditation;
  int health;
  int constitution;
  int inteligence;
  int strength;
  int agility;
};

struct ClassSkillsData {
  int recovery;
  int mana;
  int meditation;
  int health;
};

struct EquationsData{
  double limitForNextLevel;
  double dodgeAttackComparisonValue;
  double npcDamageConst;
  double critickAttackProb;
  double excessGoldConstPow;
};

struct GlobalConfig {
  int attackZoneWidth;
  int attackZoneHeight;
  int attackNpcZoneWidth;
  int attackNpcZoneHeight;
  int dropZoneWidth;
  int dropZoneHeight;
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
  double npcDropGold;
  double npcDropPotion;
  double npcDropItem;
  int goldItemId;
  int playerInitialGold;
  double npcDropGoldRandMinValue;
  double npcDropGoldRandMaxValue;
  double estimateTimeToPriestConst;
  unsigned int maxInventoryDifferentItems;
  std::map<PlayerRace, RaceSkillsData> raceSkills;
  std::map<PlayerClass, ClassSkillsData> classSkills;
  std::map<int, std::unique_ptr<Item>> items;
  std::vector<TraderItem> traderItems;
  ChatMessages chatMessages;
  DropSizes dropSizes;
  EquationsData equations;
  std::vector<int> itemsToDropNPC;
  std::vector<int> potionsToDropNPC;
  std::vector<InventoryElementData> defaultInventory;
};

struct SystemConfig {
  std::string port;
  std::string indexFile;
  std::string dbFile;
};

class GC {
  public:
    GC() {}
    GC(const GC&) = delete;
    GC& operator=(const GC&) = delete;
    GC&& operator=(GC&& other) = delete;
    static void load(const char* src);
    static const GlobalConfig& get();
    static const SystemConfig& getS();
  private:
    GlobalConfig g;
    SystemConfig s;
    static GC* instance;
    static void parseItems(GlobalConfig& g, const Json::Value& val);
    static void parseRaces(GlobalConfig& g, const Json::Value& val);
    static void parseClasses(GlobalConfig& g, const Json::Value& val);
};

#endif
