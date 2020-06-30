#include "GameConfig.h"

#include <fstream>
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
  const Json::Value items = gameConfig["items"];
  const Json::Value traderItems = gameConfig["traderItems"];

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

  /** PARSE ITEMS */
  for(const Json::Value &item : items) {
    std::string t = item["type"].asString();
    Equipable type =
      static_cast<Equipable> (t[0]);
    switch (type) {
      case Equipable::BODY_ARMOUR:
      case Equipable::POTION:
      case Equipable::WEAPON:
      case Equipable::LEFT_HAND_DEFENSE:
      case Equipable::HEAD_DEFENSE:
        break;
    default:
      return;
    }

    Item dataItem = {
      item["id"].asInt(),
      type,
      item["name"].asString()
    };
    instance->g.items.insert(
      std::pair<int, Item>(
        dataItem.id, dataItem));
  };

  // PARSE TRADER ITEMS
  for(const Json::Value &traderItem : traderItems) {
    int itemId = traderItem["itemId"].asInt();
    if (!instance->g.items.count(itemId)) continue;

    TraderItem item = {
      itemId,
      traderItem["value"].asInt()
    };
    instance->g.traderItems.push_back(item);
  };
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
