#include "EquationDefinitions.h"
#include <math.h>
#include <iostream>
#include <algorithm>

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
  RightHandEquipmentSkills weaponSkills) {
    int rand = random(weaponSkills.minDamage, weaponSkills.maxDamage);
    return strength * rand;
}

int Equations::attackExperience(
  int damage,
  int otherLevel,
  int level) {
    return damage * std::max(otherLevel - level + 10, 0);
}

int Equations::killExperience(
  int maxHealthOther, 
  int otherLevel, 
  int level) {
    return randomFloat(0, 0.1) * 
      maxHealthOther * 
      std::max(otherLevel - level + 10, 0);
}

bool Equations::dodgeAttack(int agility) {
  float rand = pow(randomFloat(0, 1), agility);
  return rand < DEFENSE_CONST;
}

int Equations::defend(
  int agility, 
  BodyEquipmentSkills bodySkills, 
  LeftHandEquipmentSkills leftSkills, 
  HeadEquipmentSkills headSkills) {
    return random(bodySkills.minDefense, bodySkills.maxDefense) + 
      random(leftSkills.minDefense, leftSkills.maxDefense) + 
      random(headSkills.minDefense, headSkills.maxDefense);
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
