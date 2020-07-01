#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "../services/ChatManager.h"
#include "../GameConfig.h"

Player::Player(MainPlayerData playerData, size_t id):
  LiveEntity(playerData.position, playerData.points, playerData.skills,
  playerData.level, id),
  nick(playerData.nick),
  gold(playerData.gold),
  experience(playerData.experience),
  rootd(playerData.rootd),
  inventory(playerData.inventory),
  movement(playerData.movement),
  equipment(playerData.equipment),
  resurrection({std::chrono::system_clock::now(), false}),
  chat(playerData.chat){
    rightSkills = {0, 0, 0, 0};
    leftSkills = {0, 0};
    bodySkills = {0, 0};
    headSkills = {0, 0};
    for (unsigned int i = 0; i < inventory.size(); i++){
      if (inventory.at(i).isEquiped)
        equip(i);
    }
}

std::unique_ptr<Player> Player::createPlayer(size_t id, std::string nick,
  PlayerRootData root) {
    MainPlayerData data;
    const GlobalConfig& c = GC::get();

    data.rootd = root;
    data.nick = nick;
    data.gold = 0;
    data.level = c.playerInitialLevel;

    Player::setClassSkills(data.skills, data.rootd);
    Player::setRaceSkills(data.skills, data.rootd);

    Player::setDefaultEquipment(data);

    data.experience.maxLevelExperience = 0;
    data.experience.currentExperience = 0;
    Player::setExperienceData(data.level, data.experience);

    Player::setPositionData(root, data.position);

    data.points.totalHP = Equations::maxLife(data.skills.classConstitution,
      data.skills.classHealth, data.skills.raceHealth,
      data.level);
    //data.points.currentHP = data.points.totalHP;
    data.points.currentHP = 1;

    data.points.totalMP = Equations::maxMana
      (data.skills.inteligence, data.skills.classMana, data.skills.raceMana,
      data.level);
    //data.points.currentMP = data.points.totalMP;
    data.points.currentMP = 0;
    data.points.lastHealthIncrease = std::chrono::system_clock::now();
    data.points.lastManaIncrease = std::chrono::system_clock::now();
    data.points.nextRespawn = std::chrono::system_clock::now();
    data.points.meditating = false;

    data.movement.xDir = 0;
    data.movement.yDir = 0;

    ChatManager::initialMessage(data.chat);

    std::unique_ptr<Player> player(new Player(data, id));

    return player;
}

void Player::setRaceSkills(SkillsData &skills, PlayerRootData &root){
  switch (root.prace){
    case HUMAN:
      skills.classRecovery = HUMAN_RECOVERY;
      skills.classMana = HUMAN_MANA;
      skills.classMeditation = HUMAN_MEDITATION;
      skills.classHealth = HUMAN_HEALTH;
      skills.classConstitution = HUMAN_CONSTITUTION;
      skills.inteligence = HUMAN_INTELIGENCE;
      skills.strength = HUMAN_STRENGTH;
      skills.agility = HUMAN_AGILITY;
      break;
    case ELF:
      skills.classRecovery = ELF_RECOVERY;
      skills.classMana = ELF_MANA;
      skills.classMeditation = ELF_MEDITATION;
      skills.classHealth = ELF_HEALTH;
      skills.classConstitution = ELF_CONSTITUTION;
      skills.inteligence = ELF_INTELIGENCE;
      skills.strength = ELF_STRENGTH;
      skills.agility = ELF_AGILITY;
      break;
    case DWARF:
      skills.classRecovery = DWARF_RECOVERY;
      skills.classMana = DWARF_MANA;
      skills.classMeditation = DWARF_MEDITATION;
      skills.classHealth = DWARF_HEALTH;
      skills.classConstitution = DWARF_CONSTITUTION;
      skills.inteligence = DWARF_INTELIGENCE;
      skills.strength = DWARF_STRENGTH;
      skills.agility = DWARF_AGILITY;
      break;
    case GNOME:
      skills.classRecovery = GNOME_RECOVERY;
      skills.classMana = GNOME_MANA;
      skills.classMeditation = GNOME_MEDITATION;
      skills.classHealth = GNOME_HEALTH;
      skills.classConstitution = GNOME_CONSTITUTION;
      skills.inteligence = GNOME_INTELIGENCE;
      skills.strength = GNOME_STRENGTH;
      skills.agility = GNOME_AGILITY;
      break;
    default:
      break;
    }
}

void Player::setClassSkills(SkillsData &skills, PlayerRootData &root){
  switch (root.pclass){
    case MAGE:
      skills.raceRecovery = MAGE_RECOVERY;
      skills.raceMana = MAGE_MANA;
      skills.raceMeditation = MAGE_MEDITATION;
      skills.raceHealth = MAGE_HEALTH;
      break;
    case CLERIC:
      skills.raceRecovery = CLERIC_RECOVERY;
      skills.raceMana = CLERIC_MANA;
      skills.raceMeditation = CLERIC_MEDITATION;
      skills.raceHealth = CLERIC_HEALTH;
      break;
    case PALADIN:
      skills.raceRecovery = PALADIN_RECOVERY;
      skills.raceMana = PALADIN_MANA;
      skills.raceMeditation = PALADIN_MEDITATION;
      skills.raceHealth = PALADIN_HEALTH;
      break;
    case WARRIOR:
      skills.raceRecovery = WARRIOR_RECOVERY;
      skills.raceMana = WARRIOR_MANA;
      skills.raceMeditation = WARRIOR_MEDITATION;
      skills.raceHealth = WARRIOR_HEALTH;
      break;
    default:
      break;
  }
}

void Player::setExperienceData(size_t &level, ExperienceData &experience){
    experience.minLevelExperience = experience.maxLevelExperience;
    experience.maxLevelExperience =
      Equations::maxLevelExperience(level);
}

void Player::setPositionData(PlayerRootData &root, PositionData &position){
  position.w = PLAYER_WIDTH;
  position.h = PLAYER_HEIGHT;
  position.x = 2600;
  position.y = 2600;
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

  int damage = Equations::damage(skills.strength, rightSkills);
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
  bool critickAttack = Equations::criticAttack();
  if (!critickAttack){
    bool dodged = Equations::dodgeAttack(skills.agility);
    if (dodged){
      ChatManager::attackDodged(chat);
      damage = -1;
      return;
    }
  }
  if (critickAttack) damage = damage * 2; // critic attack

  int defensePoints = defend();
  if (defensePoints > damage){
    damage = 0;
    return;
  }

  health.currentHP -= (damage - defensePoints);
  if (health.currentHP < 0) health.currentHP = 0;

  damage -= defensePoints;

  ChatManager::damageReceived(chat, damage);
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

      health.totalHP = Equations::maxLife(skills.classConstitution,
      skills.classHealth, skills.raceHealth,
      level);

      health.totalMP = Equations::maxMana
      (skills.inteligence, skills.classMana, skills.raceMana, level);
    }
}

int Player::defend(){
  return Equations::defend(skills.agility, bodySkills,
    leftSkills, headSkills);
}

void Player::setDefaultEquipment(MainPlayerData &data){
  InventoryElementData weapon, weapon2, leftHandArmour,
    headArmour, bodyArmour2, healthPotion, manaPotion;

  healthPotion.amount = 2;
  healthPotion.isEquiped = false;
  healthPotion.itemId = 8;

  manaPotion.amount = 2;
  manaPotion.isEquiped = false;
  manaPotion.itemId = 7;

  leftHandArmour.amount = 1;
  leftHandArmour.isEquiped = true;
  leftHandArmour.itemId = 4;

  headArmour.amount = 1;
  headArmour.isEquiped = true;
  headArmour.itemId = 3;

  bodyArmour2.amount = 1;
  bodyArmour2.isEquiped = true;
  bodyArmour2.itemId = 5;

  weapon.amount = 1;
  weapon.isEquiped = true;
  weapon.itemId = 2;
  
  weapon2.amount = 1;
  weapon2.isEquiped = false;
  weapon2.itemId = 1;

  data.inventory.push_back(weapon);
  data.inventory.push_back(weapon2);
  data.inventory.push_back(headArmour);
  data.inventory.push_back(bodyArmour2);
  data.inventory.push_back(leftHandArmour);
  data.inventory.push_back(healthPotion);
  data.inventory.push_back(manaPotion);
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
  inventory.erase (inventory.begin(), inventory.begin()+inventory.size());
}

void Player::setTimeToResurrect(
  double minDistanceToPriest){
  resurrection.resurrect = true;
  std::chrono::seconds sec(int(minDistanceToPriest*0.01));
  resurrection.timeToResurrection = std::chrono::system_clock::now() + sec;
}

void Player::setPlayerGameModelData(PlayerGameModelData &modelData){
  modelData.playerData.nick = nick;
  modelData.playerData.id = id;
  modelData.playerData.gold = gold;
  modelData.playerData.level = level;
  modelData.playerData.experience = experience;
  modelData.playerData.skills = skills;
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
  otherData.otherPlayerHealth = health.currentHP;
  otherData.resurrection = resurrection;
  otherData.healthAndMana = health;
}
