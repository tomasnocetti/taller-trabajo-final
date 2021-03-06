#include "EquationDefinitions.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include "../GameConfig.h"

Equations::Equations() {}

Equations::~Equations(){}

unsigned int Equations::seed = 0;

int Equations::maxLife(
  PlayerRootData& root,
  int level) {
    const GlobalConfig& c = GC::get();
    const RaceSkillsData& race = c.raceSkills.at(root.prace);
    const ClassSkillsData& classT = c.classSkills.at(root.pclass);
    return race.constitution * race.health * classT.health * level;
}

int Equations::maxMana(
  PlayerRootData& root,
  int level) {
    const GlobalConfig& c = GC::get();
    const RaceSkillsData& race = c.raceSkills.at(root.prace);
    const ClassSkillsData& classT = c.classSkills.at(root.pclass);
    return race.inteligence * classT.mana * race.mana * level;
}

int Equations::maxLevelExperience(int level) {
  const GlobalConfig& c = GC::get();
  return 1000 * pow(level, c.equations.limitForNextLevel);
}

int Equations::damage(
  PlayerRootData& root,
  RightHandEquipmentSkills weaponSkills) {
    const GlobalConfig& c = GC::get();
    const RaceSkillsData& race = c.raceSkills.at(root.prace);
    int rand = random(weaponSkills.minDamage, weaponSkills.maxDamage);
    return std::max(race.strength * rand, race.strength);
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

bool Equations::dodgeAttackNPC(NPCClass& npcType) {
  const GlobalConfig& c = GC::get();
  const NPCData& npcD = c.npcs.at(npcType);
  float rand = pow(randomFloat(0, 1), npcD.skills);
  return rand < c.equations.dodgeAttackComparisonValue;
}

bool Equations::dodgeAttackPlayer(PlayerRootData& root) {
  const GlobalConfig& c = GC::get();
  const RaceSkillsData& race = c.raceSkills.at(root.prace);

  float rand = pow(randomFloat(0, 1), race.agility);
  return rand < c.equations.dodgeAttackComparisonValue;
}

int Equations::defend(
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

int Equations::NPCDamage(NPCClass& npcType){
  const GlobalConfig& c = GC::get();
  const NPCData& npcD = c.npcs.at(npcType);
  return npcD.skills * npcD.level * c.equations.npcDamageConst;
}

bool Equations::criticAttack(){
  const GlobalConfig& c = GC::get();
  return randomFloat(0, 1) < c.equations.critickAttackProb;
}

int Equations::excessGold(int level, int gold){
  const GlobalConfig& c = GC::get();
  return std::max(gold - (int)(c.equations.baseGoldConst * pow(level,
    c.equations.excessGoldConstPow)), 0);
}

int Equations::maxGold(int level){
  const GlobalConfig& c = GC::get();
  return c.equations.baseGoldConst * 
    pow(level, c.equations.excessGoldConstPow) * c.equations.maxGoldFactor;
}

int Equations::recoverMana(PlayerRootData& root, bool isMeditating) {
  const GlobalConfig& c = GC::get();
  const ClassSkillsData& classT = c.classSkills.at(root.pclass);
  const RaceSkillsData& race = c.raceSkills.at(root.prace);
  int mult = isMeditating ? race.inteligence : 1;
  return classT.meditation * mult;
}

int Equations::recoverHealth(PlayerRootData& root) {
  const GlobalConfig& c = GC::get();
  const RaceSkillsData& race = c.raceSkills.at(root.prace);
  return race.recovery;
}
