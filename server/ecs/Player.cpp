#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "../services/ChatManager.h"
#include "../GameConfig.h"

#define BANK_INVENTORY 0
#define PLAYER_INVENTORY 1

Player::Player(MainPlayerData& playerData, size_t id):
  LiveEntity(playerData.position, playerData.points,
  playerData.level, id),
  nick(playerData.nick),
  gold(playerData.gold),
  experience(playerData.experience),
  rootd(playerData.rootd),
  inventory(playerData.inventory),
  equipment(playerData.equipment),
  resurrection({std::chrono::system_clock::now(), false}),
  chat(playerData.chat){
    rightSkills = {0, 0, 0, 0};
    leftSkills = {0, 0};
    bodySkills = {0, 0};
    headSkills = {0, 0};
    equipment = {0, 0, 0, 0};
    equipDefault();
}

std::unique_ptr<Player> Player::createPlayer(
  PlayerPersistData& dataP, std::string& nick) {
    MainPlayerData data;
    data.id = dataP.id;
    data.rootd = dataP.rootd;
    data.nick = nick;
    data.gold = dataP.gold;
    
    data.level = dataP.level;
    data.inventory = dataP.inventory;
    data.position = {
      dataP.positionX,
      dataP.positionY,
      PLAYER_WIDTH, PLAYER_HEIGHT};

    data.experience.currentExperience = dataP.currentExperience;
    Player::setExperienceData(data.level, data.experience);

    data.points.totalHP = Equations::maxLife(data.rootd, data.level);
    data.points.currentHP = dataP.currentHP;

    data.points.totalMP = Equations::maxMana(data.rootd, data.level);
    data.points.currentMP = dataP.currentMP;

    data.points.recoverTime = std::chrono::system_clock::now();
    data.points.nextRespawn = std::chrono::system_clock::now();
    data.points.meditating = false;

    ChatManager::initialMessage(data.chat);

    std::unique_ptr<Player> player(new Player(data, dataP.id));
    player->itemsInBank = dataP.savedInventory;
    player->goldInBank = dataP.savedGold;
    return player;
}

PlayerPersistData Player::generatePersistData(){
  PlayerPersistData p = {
    id,
    gold,
    goldInBank,
    level,
    static_cast<size_t>(health.currentHP),
    static_cast<size_t>(health.currentMP),
    experience.currentExperience,
    rootd,
    position.x,
    position.y,
    inventory,
    itemsInBank
  };
  return p;
}

void Player::setExperienceData(size_t &level, ExperienceData &experience){
  experience.minLevelExperience =
    level == 0 ? 0 : Equations::maxLevelExperience(level - 1);
  experience.maxLevelExperience =
    Equations::maxLevelExperience(level);
}

bool Player::attack(LiveEntity &entity, int xCoord, int yCoord){
  const GlobalConfig& c = GC::get();
  PositionData attackZoneData = {
    xCoord - c.attackZoneWidth / 2,
    yCoord - c.attackZoneHeight / 2,
    c.attackZoneWidth,
    c.attackZoneHeight};
  Entity attackZone(attackZoneData);

  bool canAttack = entity.checkCollision(attackZone);
  if (!canAttack) return false;

  double distanceAttackZone =  Entity::getPositionDistance(
    attackZoneData , position);
  if (distanceAttackZone > rightSkills.range) return false;

  if (health.currentMP < rightSkills.mana) return false;
  health.currentMP -= rightSkills.mana;

  int damage = Equations::damage(rootd, rightSkills);

  entity.rcvDamage(damage);
  if (damage == -1){
    ChatManager::enemyDodgedTheAttack(chat);
    return true;
  }

  ChatManager::damageCaused(chat, damage);

  addExperience(damage, entity.level, entity.health.currentHP,
    entity.health.totalHP);

  return true;
}

void Player::rcvDamage(int &damage){
  stopMeditating();

  bool critickAttack = Equations::criticAttack();
  if (!critickAttack){
    bool dodged = Equations::dodgeAttackPlayer(rootd);
    if (dodged){
      ChatManager::attackDodged(chat);
      damage = -1;
      return;
    }
  }
  if (critickAttack) damage = damage * 2; // critic attack

  int defensePoints = Equations::defend(bodySkills, leftSkills, headSkills);
  if (defensePoints > damage){
    damage = 0;
    return;
  }

  health.currentHP -= (damage - defensePoints);
  if (health.currentHP < 0) setDeadDefaults();

  damage -= defensePoints;

  ChatManager::damageReceived(chat, damage);
}

void Player::setDeadDefaults(){
  health.currentHP = 0;
  health.currentMP = 0;
}

void Player::addExperience(int &damage, size_t &otherLevel, int &otherHealth,
  int &otherMaxHEalth){
    if (otherHealth <= 0){
      experience.currentExperience += Equations::killExperience(
        otherMaxHEalth, otherLevel, level);
    }else {
      experience.currentExperience += Equations::attackExperience(
      damage, otherLevel, level);
    }

    if (experience.currentExperience >= experience.maxLevelExperience){
      level += 1;
      Player::setExperienceData(level, experience);

      health.totalHP = Equations::maxLife(rootd, level);
      health.totalMP = Equations::maxMana(rootd, level);
    }
}

void Player::equipDefault(){
  const GlobalConfig& c = GC::get();

  for (unsigned int i = 0; i < inventory.size(); i++){
    bool canEquip = true;

    for (auto& it : c.potionsToDropNPC){
      if (inventory.at(i).itemId == it){
        canEquip = false;
        inventory.at(i).isEquiped = false;
        break;
      }
    }

    if (!canEquip) continue;

    equip(i);
  }
}

void Player::equip(int inventoryPosition){
  if ((unsigned int)inventoryPosition >= inventory.size()) return;
  Equipable type;
  const GlobalConfig& c = GC::get();

  InventoryElementData& i = inventory[inventoryPosition];

  const std::unique_ptr<Item> &item = c.items.at(i.itemId);

  type = item->type;

  switch (type) {
    case HEALTH_POTION:
    case MANA_POTION:
      item->equip(*this);

      inventory[inventoryPosition].amount -= 1;

      if (inventory[inventoryPosition].amount > 0) return;

      inventory.erase(inventory.begin() + inventoryPosition);
      break;
    case WEAPON:
    case LEFT_HAND_DEFENSE:
    case HEAD_DEFENSE:
    case BODY_ARMOUR:
      item->equip(*this);

      for (auto& it : inventory){
        if (c.items.at(it.itemId)->type != type) continue;
        it.isEquiped = false;
      }

      inventory[inventoryPosition].isEquiped = true;
      break;
  }
}

void Player::drop(){
  const GlobalConfig& c = GC::get();

  for (unsigned int i = 0; i < inventory.size(); i++){
    InventoryElementData& j = inventory[i];
    const std::unique_ptr<Item> &item = c.items.at(j.itemId);
    item->unEquip(*this);
  }

  inventory.erase(inventory.begin(), inventory.begin() + inventory.size());
}

int Player::calculateExcessGold(){
  return Equations::excessGold(level, gold);
}

void Player::setTimeToResurrect(double minDistanceToPriest){
  const GlobalConfig& c = GC::get();
  resurrection.resurrect = true;

  int resurrectionTime = minDistanceToPriest * c.estimateTimeToPriestConst;
  std::chrono::seconds sec(resurrectionTime);
  resurrection.timeToResurrection = std::chrono::system_clock::now() + sec;

  ChatManager::resurrecting(chat, resurrectionTime);
}

bool Player::throwObj(size_t inventoryPosition,
  InventoryElementData &itemToDrop, PositionData &dropFirstPos){
    if ((unsigned int)inventoryPosition >= inventory.size()) return false;

    itemToDrop = inventory.at(inventoryPosition);
    dropFirstPos = position;

    bool success = eraseInventoryItem(inventoryPosition, PLAYER_INVENTORY);
    return success;    
}

bool Player::eraseInventoryItem(size_t inventoryPosition, int opt){
  std::vector<InventoryElementData> &aux =
    (opt == PLAYER_INVENTORY) ? inventory : itemsInBank;  

  if ((unsigned int)inventoryPosition >= aux.size()) return false;

  Equipable type;
  const GlobalConfig& c = GC::get();

  InventoryElementData& i = aux[inventoryPosition];

  const std::unique_ptr<Item> &item = c.items.at(i.itemId);

  type = item->type;

  switch (type) {
    case HEALTH_POTION:
    case MANA_POTION:
      aux[inventoryPosition].amount -= 1;

      if (aux[inventoryPosition].amount > 0) return true;

      aux.erase(aux.begin() + inventoryPosition);
      return true;
      break;
    case WEAPON:
    case LEFT_HAND_DEFENSE:
    case HEAD_DEFENSE:
    case BODY_ARMOUR:
      aux[inventoryPosition].amount -= 1;

      if (aux[inventoryPosition].amount > 0) return true;

      if (!aux[inventoryPosition].isEquiped){
        aux.erase(aux.begin() + inventoryPosition);
        return true;
      }

      item->unEquip(*this);
      aux.erase(inventory.begin() + inventoryPosition);
  }
  return true;
}

void Player::setPlayerGameModelData(PlayerGameModelData &modelData){
  modelData.playerData.nick = nick;
  modelData.playerData.id = id;
  modelData.playerData.gold = gold;
  modelData.playerData.level = level;
  modelData.playerData.experience = experience;
  modelData.playerData.rootd = rootd;
  modelData.playerData.inventory = inventory;
  modelData.playerData.points = health;
  modelData.playerData.position = position;
  modelData.playerData.movement = movement;
  modelData.playerData.equipment = equipment;
  modelData.playerData.chat = chat;
}

void Player::setOtherPlayersData(OtherPlayersData &otherData){
  otherData.id = id;
  otherData.position = position;
  otherData.movement = movement;
  otherData.rootd = rootd;
  otherData.equipment = equipment;
  otherData.resurrection = resurrection;
  otherData.healthAndMana = health;
}

void Player::recover() {
  health.recoverTime = std::chrono::system_clock::now();

  health.currentMP += Equations::recoverMana(rootd, health.meditating);
  if (health.currentMP > health.totalMP)
    health.currentMP = health.totalMP;

  health.currentHP += Equations::recoverHealth(rootd);
  if (health.currentHP > health.totalHP)
    health.currentHP = health.totalHP;
}

void Player::meditate(){
  health.meditating = true;
  ChatManager::meditating(chat);
}

void Player::stopMeditating(){
  if (health.meditating){
    ChatManager::stopMeditating(chat);
    health.meditating = false;
  }
}

bool Player::pickUp(DropItemData &drop){
  const GlobalConfig& c = GC::get();
  PositionData pickUpZoneData = {
    drop.position.x - c.dropZoneWidth / 2,
    drop.position.y - c.dropZoneHeight / 2,
    c.dropZoneWidth,
    c.dropZoneHeight};
  Entity pickUpZone(pickUpZoneData);

  bool canPickUp = checkCollision(pickUpZone);
  if (!canPickUp) return false;

  if (drop.id == c.goldItemId){
    gold += drop.amount;

    unsigned int maxGold = Equations::maxGold(level);
    if (gold < maxGold) return true;

    gold = maxGold;
    ChatManager::maxGold(chat);
    return true;
  }

  InventoryElementData item = {drop.amount, false, drop.id};

  return addItemToInventory(item, PLAYER_INVENTORY);
}

bool Player::addItemToInventory(InventoryElementData &item, int opt){
  std::vector<InventoryElementData> &aux =
    (opt == PLAYER_INVENTORY) ? inventory : itemsInBank;   

  for (auto& it : aux){
    if (it.itemId == item.itemId){
      it.amount += item.amount;
      return true;
    }
  }

  if (inventoryIsFull(opt)) return false;

  aux.push_back(std::move(item));
  return true;
}

bool Player::inventoryIsFull(size_t opt){
  std::vector<InventoryElementData> &aux =
    (opt == PLAYER_INVENTORY) ? inventory : itemsInBank;  

  const GlobalConfig& c = GC::get();
  if (aux.size() >= c.maxInventoryDifferentItems){
    ChatManager::inventoryIsFull(chat);
    return true;
  }
  return false;
}

bool Player::isAlive(){
  return health.currentHP > 0;
}

void Player::sendMessage(MessageType type, std::string msg){
  ChatManager::otherMessages(chat, msg, type);
}

void Player::buy(size_t itemValue, size_t itemId){
  if (gold < itemValue){
    ChatManager::insufficientFunds(chat);
    return;
  }

  InventoryElementData newItem = {1, false, (int)itemId};
  bool success = addItemToInventory(newItem, PLAYER_INVENTORY);

  if (!success) return;

  gold -= itemValue;
  ChatManager::successfullBuy(chat, itemValue);
}

void Player::sell(size_t inventoryPos, size_t itemValue){
  if (inventoryPos > inventory.size()){
    ChatManager::invalidOption(chat);
  }

  eraseInventoryItem(inventoryPos, PLAYER_INVENTORY);
  gold += itemValue;

  ChatManager::successfullSell(chat, itemValue);

  unsigned int maxGold = Equations::maxGold(level);
  if (gold > maxGold){
    gold = maxGold;
    ChatManager::maxGold(chat);
  }
}

size_t Player::inventoryItemId(size_t inventoryPosition, int opt){
  std::vector<InventoryElementData> &aux =
    (opt == PLAYER_INVENTORY) ? inventory : itemsInBank;  

  return aux.at(inventoryPosition).itemId;
}

void Player::heal(){
  stopMeditating();
  health.currentHP = health.totalHP;
  health.currentMP = health.totalMP;
}

void Player::depositGold(size_t amount){
  if (amount > gold){
    ChatManager::insufficientFunds(chat);
    return;
  }
  goldInBank += amount;
  gold -= amount;
  ChatManager::depositGoldSuccess(chat, goldInBank);
}

void Player::depositItem(size_t inventoryPos){
  if (inventoryPos >= inventory.size()){
    ChatManager::invalidOption(chat);
    return;
  }

  InventoryElementData newItem = {
    1, 
    false, 
    (int)inventoryItemId(inventoryPos, PLAYER_INVENTORY)};
  bool success = addItemToInventory(newItem, BANK_INVENTORY);

  if (!success) return;

  eraseInventoryItem(inventoryPos, PLAYER_INVENTORY);
  ChatManager::depositItemSuccess(chat);
}

void Player::withdrawGold(size_t amount){
  if (amount > goldInBank){
    ChatManager::insufficientFunds(chat);
    return;
  }
  goldInBank -= amount;
  gold += amount;
  ChatManager::successfullGoldExtraction(chat, goldInBank);
}

void Player::withdrawItem(size_t inventoryPos){
  if (inventoryPos >= itemsInBank.size()){
    ChatManager::invalidOption(chat);
    return;
  }

  InventoryElementData newItem = {
    1, 
    false, 
    (int)inventoryItemId(inventoryPos, BANK_INVENTORY)};
  bool success = addItemToInventory(newItem, PLAYER_INVENTORY);

  if (!success){
    ChatManager::inventoryIsFull(chat);
    return;
  }

  eraseInventoryItem(inventoryPos, BANK_INVENTORY);
  ChatManager::successfullItemExtraction(chat);
}
