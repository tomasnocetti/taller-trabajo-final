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
    int damage(int strength, RightHandEquipmentSkills weaponSkills);
    int attackExperience(int damage, int otherLevel, int level);
    int killExperience(int maxHealthOther, int otherLevel, int level);
    bool dodgeAttack(int agility);
    int defend(int agility, BodyEquipmentSkills bodySkills, 
    LeftHandEquipmentSkills leftSkills, HeadEquipmentSkills headSkills);
    int random(int minValue, int maxValue);
    float randomFloat(float a, float b);
  private:
    unsigned int seed;
};

#endif
