#include "EquationDefinitions.h"
#include <math.h>
#include <random>

#define MAX_LEVEL_EXPERIENCE_CONST 1.8

Equations::Equations(){}

Equations::~Equations(){}

int Equations::maxLife(
  int constitution,
  int classLife,
  int raceLife,
  int level) {
    return constitution * classLife * raceLife * level;
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
    std::mt19937 generator; 
    /* DañoArmaMin, DañoArmaMax */
    std::uniform_int_distribution<> distribution(1, 6); 
    return strength * distribution(generator);
}

int Equations::attackExperience(
  int damage,
  int otherLevel,
  int level) {}

int Equations::killExperience(
  int maxLifeOther, 
  int otherLevel, 
  int level) {}

bool Equations::dodgeAttack(int agility) {}

int Equations::defend(
  int agility, 
  BodyEquipment bodyArmour, 
  LeftHandEquipment shield, 
  HeadEquipment helmet) {}