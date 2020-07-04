#ifndef EQUATIONS_H
#define EQUATIONS_H

#include "../../definitions/EquipmentDefinitions.h"
#include "../../DataDefinitions.h"

class Equations{
  public:
    Equations();
    ~Equations();
    static int maxLife(PlayerRootData& root, int level);
    static int maxMana(PlayerRootData& root, int level);
    static int maxLevelExperience(int level);
    static int recoverMana(PlayerRootData& root, bool isMeditating);
    static int recoverHealth(PlayerRootData& root);
    static int damage(PlayerRootData& root, 
      RightHandEquipmentSkills weaponSkills);
    static int attackExperience(int damage, int otherLevel, int level);
    static int killExperience(int maxHealthOther, int otherLevel, int level);
    static bool dodgeAttackPlayer(PlayerRootData& root);
    static bool dodgeAttackNPC(NPCClass& npcType);
    static int defend(
      BodyEquipmentSkills bodySkills, 
      LeftHandEquipmentSkills leftSkills, HeadEquipmentSkills headSkills);
    static int random(int minValue, int maxValue);
    static float randomFloat(float a, float b);
    static int NPCDamage(NPCClass& npcType);
    static bool criticAttack();
    static int excessGold(int level, int gold);
    static int maxGold(int level);
    
  private:
    static unsigned int seed;
};

#endif
