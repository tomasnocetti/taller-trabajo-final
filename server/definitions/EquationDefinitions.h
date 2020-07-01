#ifndef EQUATIONS_H
#define EQUATIONS_H

#include "../../definitions/EquipmentDefinitions.h"

class Equations{
  public:
    Equations();
    ~Equations();
    static int maxLife(int constitution, int classHealth, 
      int raceHealth, int level);
    static int maxMana(int inteligence, int classMana, int raceMana, int level);
    static int maxLevelExperience(int level);
    static int damage(int strength, RightHandEquipmentSkills weaponSkills);
    static int attackExperience(int damage, int otherLevel, int level);
    static int killExperience(int maxHealthOther, int otherLevel, int level);
    static bool dodgeAttack(int agility);
    static int defend(int agility, BodyEquipmentSkills bodySkills, 
      LeftHandEquipmentSkills leftSkills, HeadEquipmentSkills headSkills);
    static int random(int minValue, int maxValue);
    static float randomFloat(float a, float b);
    static int NPCDamage(int level, size_t npcStrength);
    static bool criticAttack();
    static int excessGold(int level, int gold);
  private:
    static unsigned int seed;
};

#endif
