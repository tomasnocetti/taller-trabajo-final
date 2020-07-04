#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_


#if __APPLE__
#include <json/json.h>
#else
#include <jsoncpp/json/json.h>
#endif

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "definitions/Items.h"
#include "../DataDefinitions.h"

#define ERROR_MSG "No valid instance"
#define INVALID_CONFIG_FILE "Invalid config file"
#define INVALID_DB_FILE "Invalid db file path"
#define INVALID_INDEX_FILE "Invalid index file path"
#define INVALID_MAP_FILE_P "Invalid map file path"

struct InterchangeableItem {
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
  std::string successfullSell;
  std::string resurrecting;
  std::string invalidCommandBuy;
  std::string invalidCommandSell;
  std::string traderDontBuyThatItem;
  std::string successfullBuy;
  std::string maxGold;
  std::string invalidCommandHeal;
  std::string depositGoldSuccess;
  std::string invalidCommand;
  std::string invalidCommandDepositWithdraw;
  std::string depositItemSuccess;
  std::string successfullGoldExtraction;
  std::string successfullItemExtraction;
  std::string playerNotOnline;
  std::string playerDoesNotExit;
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
  double npcDropGoldRandMinValue;
  double npcDropGoldRandMaxValue;
  double npcDropGold;
  double npcDropPotion;
  double npcDropItem;
  double maxGoldFactor;
  int baseGoldConst;
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
  size_t playerInitialLevel;
  size_t newbieLevel;
  size_t fairPlayLevel;
  int goldItemId;
  double estimateTimeToPriestConst;
  unsigned int maxInventoryDifferentItems;
  size_t playerInitialGold;
  unsigned int traderBankerPriestMinRangeToInteract;
  double traderFactorWhenSelling;
  std::map<PlayerRace, RaceSkillsData> raceSkills;
  std::map<PlayerClass, ClassSkillsData> classSkills;
  std::map<int, std::unique_ptr<Item>> items;
  std::vector<InterchangeableItem> traderItems;
  std::vector<InterchangeableItem> priestItems;
  ChatMessages chatMessages;
  DropSizes dropSizes;
  EquationsData equations;
  std::vector<int> itemsToDropNPC;
  std::vector<int> potionsToDropNPC;
  std::vector<InventoryElementData> defaultInventory;
};

struct SystemConfig {
  std::string mapFile;
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
    static void clean();
    static const GlobalConfig& get();
    static const SystemConfig& getS();
  private:
    GlobalConfig g;
    SystemConfig s;
    static std::unique_ptr<GC> instance;
    static void parseSystem(SystemConfig& s, const Json::Value& val);
    static void parseItems(GlobalConfig& g, const Json::Value& val);
    static void parseRaces(GlobalConfig& g, const Json::Value& val);
    static void parseClasses(GlobalConfig& g, const Json::Value& val);
};

#endif
