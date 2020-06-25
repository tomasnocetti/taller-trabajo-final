#include "EquationDefinitions.h"
#include <math.h>
#include <iostream>

#define MAX_LEVEL_EXPERIENCE_CONST 1.8
#define DEFENSE_CONST 0.2

Equations::Equations() : seed(0) {}

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
    int rand = random(1, 6);
    return strength * rand;
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
  float rand = pow(randomFloat(0, 1), agility);
  std::cout << rand << std::endl;
  return rand < DEFENSE_CONST;
}

int Equations::defend(
  int agility, 
  BodyEquipment bodyArmour, 
  LeftHandEquipment shield, 
  HeadEquipment helmet) {
    return 0;
}

int Equations::random(int minValue, int maxValue){
  int range = (maxValue + 1) - minValue;
  return rand_r(&seed) % range + minValue;
}

float Equations::randomFloat(float a, float b) {
  float random = ((float) rand_r(&seed)) / (float) RAND_MAX;
  float diff = b - a;
  float r = random * diff;
  return a + r;
}
