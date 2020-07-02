#include "GameConfig.h"

#include <fstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>

GC* GC::instance = nullptr;

void GC::load(const char* src) {
  Json::Value root;

  std::ifstream file(src, std::ifstream::binary);
  if ((file.rdstate() & std::ifstream::failbit ) != 0)
    throw std::invalid_argument(INVALID_CONFIG_FILE);

  instance = new GC();
  file >> root;

  const Json::Value gameConfig = root["gameConfig"];
  const Json::Value races = gameConfig["races"];
  const Json::Value classes = gameConfig["classes"];
  const Json::Value items = gameConfig["items"];
  const Json::Value traderItems = gameConfig["traderItems"];
  const Json::Value chatMessages = gameConfig["chatMessages"];
  const Json::Value dropSizes = gameConfig["dropSizes"];
  const Json::Value itemsToDropNPC = gameConfig["itemsToDropNPC"];
  const Json::Value potionsToDropNPC = gameConfig["potionsToDropNPC"];
  const Json::Value equations = gameConfig["equations"];
  const Json::Value defaultInventory = gameConfig["defaultInventory"];

  instance->g.attackZoneWidth = gameConfig["attackZoneWidth"].asInt();
  instance->g.attackZoneHeight = gameConfig["attackZoneHeight"].asInt();
  instance->g.attackNpcZoneWidth = gameConfig["attackNpcZoneWidth"].asInt();
  instance->g.attackNpcZoneHeight = gameConfig["attackNpcZoneHeight"].asInt();
  instance->g.maxRangeZone = gameConfig["maxRangeZone"].asInt();
  instance->g.offsetToRespawn = gameConfig["offsetToRespawn"].asInt();
  instance->g.minDistanceNpc = gameConfig["minDistanceNpc"].asInt();
  instance->g.minDistanceToAttackPlayer =
    gameConfig["minDistanceToAttackPlayer"].asInt();
  instance->g.speed = gameConfig["speed"].asInt();
  instance->g.speedNpc = gameConfig["speedNpc"].asInt();
  instance->g.respawnTimeNpc = gameConfig["respawnTimeNpc"].asInt();
  instance->g.attackInterval = gameConfig["attackInterval"].asInt();
  instance->g.npcRandomDrop = gameConfig["npcRandomDrop"].asDouble();
  instance->g.npcInitHealthPoints = gameConfig["npcInitHealthPoints"].asInt();
  instance->g.npcInitSkills = gameConfig["npcInitSkills"].asInt();
  instance->g.playerInitialLevel = gameConfig["playerInitialLevel"].asInt();
  instance->g.newbieLevel = gameConfig["newbieLevel"].asInt();
  instance->g.fairPlayLevel = gameConfig["fairPlayLevel"].asInt();
  instance->g.npcDropGold = gameConfig["npcDropGold"].asDouble();
  instance->g.npcDropPotion = gameConfig["npcDropPotion"].asDouble();
  instance->g.npcDropItem = gameConfig["npcDropItem"].asDouble();
  instance->g.goldItemId = gameConfig["goldItemId"].asInt();
  instance->g.playerInitialGold = gameConfig["playerInitialGold"].asInt();
  instance->g.dropSizes.weight = dropSizes["weight"].asInt();
  instance->g.dropSizes.height = dropSizes["height"].asInt();
  instance->g.npcDropGoldRandMinValue =
    gameConfig["npcDropGoldRandMinValue"].asDouble();
  instance->g.npcDropGoldRandMaxValue =
    gameConfig["npcDropGoldRandMinValue"].asDouble();

  instance->g.chatMessages.initialMsg =
    chatMessages["initialMsg"].asString();
  instance->g.chatMessages.damageRcvMsg =
    chatMessages["damageRcvMsg"].asString();
  instance->g.chatMessages.enemyDodgedAttack =
    chatMessages["enemyDodgedAttack"].asString();
  instance->g.chatMessages.attackDodged =
    chatMessages["attackDodged"].asString();
  instance->g.chatMessages.damageCaused =
    chatMessages["damageCaused"].asString();
  instance->g.chatMessages.insufficientFunds =
    chatMessages["insufficientFunds"].asString();
  instance->g.chatMessages.noInventorySpace =
    chatMessages["noInventorySpace"].asString();
  instance->g.chatMessages.invalidOption =
    chatMessages["invalidOption"].asString();

  instance->g.equations.critickAttackProb =
    equations["critickAttackProb"].asDouble();
  instance->g.equations.dodgeAttackComparisonValue =
    equations["dodgeAttackComparisonValue"].asDouble();
  instance->g.equations.excessGoldConstPow =
    equations["excessGoldConstPow"].asDouble();
  instance->g.equations.limitForNextLevel =
    equations["limitForNextLevel"].asDouble();
  instance->g.equations.npcDamageConst =
    equations["npcDamageConst"].asDouble();

  /** PARSE ITEMS */
  for (const Json::Value &item : items) {
    std::string t = item["type"].asString();
    Equipable type =
      static_cast<Equipable> (t[0]);
    int id = item["id"].asInt();
    std::string name = item["name"].asString();
    switch (type) {
      case Equipable::BODY_ARMOUR:
      instance->g.items.insert(
        std::pair<int, std::unique_ptr<Item>>(
          id, std::unique_ptr<Item> (new BodyItem(
            id,
            type,
            name,
            item["minDefense"].asInt(),
            item["maxDefense"].asInt()))));
        break;
      case Equipable::MANA_POTION:
        instance->g.items.insert(
          std::pair<int, std::unique_ptr<Item>>(
            id, std::unique_ptr<Item> (new ManaPotion(
              id,
              type,
              name))));
        break;
      case Equipable::HEALTH_POTION:
        instance->g.items.insert(
          std::pair<int, std::unique_ptr<Item>>(
            id, std::unique_ptr<Item> (new HealthPotion(
              id,
              type,
              name))));
        break;
      case Equipable::WEAPON:
        instance->g.items.insert(
          std::pair<int, std::unique_ptr<Item>>(
            id, std::unique_ptr<Item> (new RightHandItem(
              id,
              type,
              name,
              item["minDamage"].asInt(),
              item["maxDamage"].asInt(),
              item["mana"].asInt(),
              item["range"].asInt()))));
        break;
      case Equipable::LEFT_HAND_DEFENSE:
        instance->g.items.insert(
          std::pair<int, std::unique_ptr<Item>>(
            id, std::unique_ptr<Item> (new LeftHandItem(
              id,
              type,
              name,
              item["minDefense"].asInt(),
              item["maxDefense"].asInt()))));
        break;
      case Equipable::HEAD_DEFENSE:
        instance->g.items.insert(
          std::pair<int, std::unique_ptr<Item>>(
            id, std::unique_ptr<HeadItem> (new HeadItem(
          id,
          type,
          name,
          item["minDefense"].asInt(),
          item["maxDefense"].asInt()))));
        break;
    default:
      return;
    }
  }

  // PARSE TRADER ITEMS
  for (const Json::Value &traderItem : traderItems) {
    int itemId = traderItem["itemId"].asInt();
    if (!instance->g.items.count(itemId)) continue;

    TraderItem item = {
      itemId,
      traderItem["value"].asInt()
    };
    instance->g.traderItems.push_back(item);
  }

  parseRaces(instance->g, races);
  parseClasses(instance->g, classes);

  // PARSE ITEMSTODROPNPC
  for (const Json::Value &item : itemsToDropNPC) {
    instance->g.itemsToDropNPC.push_back(item.asInt());
  }

  // PARSE POTIONSTODROPNPC
  for (const Json::Value &potion : potionsToDropNPC) {
    instance->g.potionsToDropNPC.push_back(potion.asInt());
  }

  // DEFAULT INVENTORY
  for (const Json::Value &inventoryItem : defaultInventory) {
    int itemId = inventoryItem["itemId"].asInt();
    int amount = inventoryItem["amount"].asInt();

    InventoryElementData item = {
      size_t(amount),
      true,
      itemId,
    };
    instance->g.defaultInventory.push_back(item);
  }
}

// RaceSkillsData GC::getRaceSkills(PlayerRace race){
//   return raceData.at(race);
// }

// void Player::getClassSkills(PlayerClass class){
//   return classData.at(class);
// }

const GlobalConfig& GC::get() {
  if (instance == nullptr) {
    throw std::runtime_error(ERROR_MSG);
  }

  return instance->g;
}

void GC::parseRaces(GlobalConfig& g, const Json::Value& val) {
  for (const Json::Value &race : val) {
    std::string t = race["type"].asString();
    PlayerRace type =
      static_cast<PlayerRace> (t[0]);
    g.raceSkills.insert(
      std::pair<PlayerRace, RaceSkillsData>(
        type,
        { race["recovery"].asInt(),
          race["mana"].asInt(),
          race["meditation"].asInt(),
          race["health"].asInt(),
          race["constitution"].asInt(),
          race["inteligence"].asInt(),
          race["strength"].asInt(),
          race["agility"].asInt()}));
  }
};

void GC::parseClasses(GlobalConfig& g, const Json::Value& val) {
  for (const Json::Value &classT : val) {
    std::string t = classT["type"].asString();
    PlayerClass type =
      static_cast<PlayerClass> (t[0]);
    g.classSkills.insert(
      std::pair<PlayerClass, ClassSkillsData>(
        type,
        { classT["recovery"].asInt(),
          classT["mana"].asInt(),
          classT["meditation"].asInt(),
          classT["health"].asInt() }));
  }
};
