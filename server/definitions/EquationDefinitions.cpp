#include "EquationDefinitions.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include "../GameConfig.h"

Equations::Equations() {}

Equations::~Equations(){}

unsigned int Equations::seed = 0;

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
  const GlobalConfig& c = GC::get();
  return 1000 * pow(level, c.equations.limitForNextLevel);
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
  const GlobalConfig& c = GC::get();
  float rand = pow(randomFloat(0, 1), agility);
  return rand < c.equations.dodgeAttackComparisonValue;
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

int Equations::NPCDamage(int level, size_t npcStrength){
  const GlobalConfig& c = GC::get();
  return npcStrength * level * c.equations.npcDamageConst;
}

bool Equations::criticAttack(){
  const GlobalConfig& c = GC::get();
  return randomFloat(0, 1) < c.equations.critickAttackProb;
}

int Equations::excessGold(int level, int gold){
  const GlobalConfig& c = GC::get();
  return std::max(gold - (int)(100 * pow(level, 
    c.equations.excessGoldConstPow)), 0);
}
