#ifndef EQUATIONS_H
#define EQUATIONS_H

#include "../../definitions/EquipmentDefinitions.h"

class Equations{
  public:
    Equations();
    ~Equations();
    int maxLife(int constitution, int classHealth, int raceHealth, int level);
    int maxMana(int inteligence, int classMana, int raceMana, int level);
    int maxLevelExperience(int level);
    int damage(int strength, RightHandEquipment weapon);
    int attackExperience(int damage, int otherLevel, int level);
    int killExperience(int maxHealthOther, int otherLevel, int level);
    bool dodgeAttack(int agility);
    int defend(int agility, BodyEquipment bodyArmour, 
      LeftHandEquipment shield, HeadEquipment helmet);
    int random(int minValue, int maxValue);
    float randomFloat(float a, float b);
  private:
    unsigned int seed;
};

#endif
