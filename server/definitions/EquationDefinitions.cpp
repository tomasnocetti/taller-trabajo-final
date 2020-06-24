#include "EquationDefinitions.h"
#include <math.h>

#define MAX_LEVEL_EXPERIENCE_CONST 1.8

Equations::Equations(){}

Equations::~Equations(){}

int Equations::maxLife(
  int constitution,
  int classHealth,
  int raceHealth,
  int level) {
    return constitution * classHealth * raceHealth * level;
}

int Equations::maxMana(
  int inteligence,
  int classMana,
  int raceMana,
  int level) {
    return inteligence * classMana * raceMana * level;
}

int Equations::maxLevelExperience(int level) {
  return 1000 * pow(level, MAX_LEVEL_EXPERIENCE_CONST);
}

int Equations::damage(
  int strength,
  RightHandEquipment weapon) {
    return strength * 2;
}

int Equations::attackExperience(
  int damage,
  int otherLevel,
  int level) {
    return 0;
}

int Equations::killExperience(
  int maxHealthOther, 
  int otherLevel, 
  int level) {
    return 0;
}

bool Equations::dodgeAttack(int agility) {
  return false;
}

int Equations::defend(
  int agility, 
  BodyEquipment bodyArmour, 
  LeftHandEquipment shield, 
  HeadEquipment helmet) {
    return 0;
}