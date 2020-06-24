#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

Player::Player(MainPlayerData playerData, size_t id) :
  LiveEntity(playerData.position, playerData.points),
  id(id),
  nick(playerData.nick),
  gold(playerData.gold),
  levelExperienceSkills(playerData.levelExperienceSkills),
  rootd(playerData.rootd),
  inventory(playerData.inventory),
  movement(playerData.movement),
  equipment(playerData.equipment) {}

Player::Player(size_t id, std::string nick, PlayerRootData root, 
PositionData p, HealthAndManaData h) : 
  LiveEntity(p, h),
  id(id),
  nick(nick),
  rootd(root){
    gold = 0;
    levelExperienceSkills.level = 1;

    int classRecovery, classMana, classMeditation, classHealth, 
      classConstitution, raceRecovery, raceMana, raceMeditation, raceHealth, 
      width = 25, height = 35;

    switch (rootd.pclass){
      case HUMAN:
        classRecovery = HUMAN_RECOVERY;
        classMana = HUMAN_MANA;
        classMeditation = HUMAN_MEDITATION;
        classHealth = HUMAN_HEALTH;
        classConstitution = HUMAN_CONSTITUTION;
        levelExperienceSkills.inteligence = HUMAN_INTELIGENCE;
        levelExperienceSkills.strength = HUMAN_STRENGTH;
        levelExperienceSkills.agility = HUMAN_AGILITY;
        width = 25;
        height = 48;
        break;
      case ELF:
        classRecovery = ELF_RECOVERY;
        classMana = ELF_MANA;
        classMeditation = ELF_MEDITATION;
        classHealth = ELF_HEALTH;
        classConstitution = ELF_CONSTITUTION;
        levelExperienceSkills.inteligence = ELF_INTELIGENCE;
        levelExperienceSkills.strength = ELF_STRENGTH;
        levelExperienceSkills.agility = ELF_AGILITY;
        break;
      case DWARF:
        classRecovery = DWARF_RECOVERY;
        classMana = DWARF_MANA;
        classMeditation = DWARF_MEDITATION;
        classHealth = DWARF_HEALTH;
        classConstitution = DWARF_CONSTITUTION;
        levelExperienceSkills.inteligence = DWARF_INTELIGENCE;
        levelExperienceSkills.strength = DWARF_STRENGTH;
        levelExperienceSkills.agility = DWARF_AGILITY;
        break;
      case GNOME:
        classRecovery = GNOME_RECOVERY;
        classMana = GNOME_MANA;
        classMeditation = GNOME_MEDITATION;
        classHealth = GNOME_HEALTH;
        classConstitution = GNOME_CONSTITUTION;
        levelExperienceSkills.inteligence = GNOME_INTELIGENCE;
        levelExperienceSkills.strength = GNOME_STRENGTH;
        levelExperienceSkills.agility = GNOME_AGILITY;
        break;
      default:
      break;
    }

    switch (rootd.prace){
      case MAGE:
        raceRecovery = MAGE_RECOVERY;
        raceMana = MAGE_MANA;
        raceMeditation = MAGE_MEDITATION;
        raceHealth = MAGE_HEALTH;
      break;
      case CLERIC:
        raceRecovery = CLERIC_RECOVERY;
        raceMana = CLERIC_MANA;
        raceMeditation = CLERIC_MEDITATION;
        raceHealth = CLERIC_HEALTH;
      break;
      case PALADIN:
        raceRecovery = PALADIN_RECOVERY;
        raceMana = PALADIN_MANA;
        raceMeditation = PALADIN_MEDITATION;
        raceHealth = PALADIN_HEALTH;
      break;
      case WARRIOR:
        raceRecovery = WARRIOR_RECOVERY;
        raceMana = WARRIOR_MANA;
        raceMeditation = WARRIOR_MEDITATION;
        raceHealth = WARRIOR_HEALTH;
      default:
      break;
    }

    levelExperienceSkills.maxLevelExperience = 
      gameEquations.maxLevelExperience(levelExperienceSkills.level);
    levelExperienceSkills.currentExperience = 0;
    
    inventory.helmet = "";
    
    LiveEntity::position = {100 , 100, width, height};
    LiveEntity::health.totalHP = gameEquations.maxLife(classConstitution, 
      classHealth, raceHealth, levelExperienceSkills.level);
    LiveEntity::health.currentHP = LiveEntity::health.totalHP;
    LiveEntity::health.totalMP = gameEquations.maxMana
      (levelExperienceSkills.inteligence, classMana, raceMana, 
      levelExperienceSkills.level);
    LiveEntity::health.currentMP = LiveEntity::health.totalMP;

    movement.xDir = 0;
    movement.yDir = 0;
    
    equipment.body = TUNIC;
    equipment.head = HELMET;
    equipment.leftHand = SHIELD;    
    equipment.rightHand = SWORD;

    if (classRecovery == -1 && classMeditation == -1 && raceRecovery == -1 &&
      raceMeditation == -1) return;
}

Player::~Player(){}

void Player::attack(LiveEntity &entity, int xCoord, int yCoord){
  PositionData attackZoneData = {
    xCoord,
    yCoord,
    ATTACK_ZONE_WIDTH,
    ATTACK_ZONE_HEIGHT};
  Entity attackZone(attackZoneData);
  
  bool attackSuccess = entity.checkCollision(attackZone);
  
  if (!attackSuccess) return;

  entity.rcvDamage();
}
