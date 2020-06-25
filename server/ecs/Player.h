#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../definitions/EquationDefinitions.h"
#include "../GameModel.h"
#include <string>

class Equation;

class Player : public LiveEntity{
  private:
    size_t id;
    std::string nick;
    size_t gold;
    ExperienceData experience;
    PlayerRootData rootd;
    Inventory inventory;
    MovementData movement;
    EquipmentData equipment;
    Equations gameEquations;
    RightHandEquipmentSkills rightSkills;
    LeftHandEquipmentSkills leftSkills;
    BodyEquipmentSkills bodySkills;
    HeadEquipmentSkills headSkills;
    friend class GameModel;

  public:
    Player(MainPlayerData playerData, size_t id);
    ~Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    int attack(LiveEntity &entity, int xCoord, int yCoord) override;
    void rcvDamage(int &damage) override;
    int defend();
    void addExperience(int &damage, size_t &otherLevel, int &otherHealth,
      int &otherMaxHealth);
    static std::unique_ptr<Player> createPlayer(
      size_t id, 
      std::string nick, 
      PlayerRootData root);
    static void setClassSkills(SkillsData &skills, PlayerRootData &root);
    static void setRaceSkills(SkillsData &skills, PlayerRootData &root);  
    static void setInitEquipment(EquipmentData &equipment, 
      PlayerRootData &root);   
    static void setRighHandSkills(RightHandEquipmentSkills
      &rightSkills, RightHandEquipment &rightEquipment);
    static void setLeftHandSkills(LeftHandEquipmentSkills
      &leftSkills, LeftHandEquipment &leftEquipment); 
    static void setBodySkills(BodyEquipmentSkills
      &bodySkills, BodyEquipment &bodyEquipment); 
    static void setHeadSkills(HeadEquipmentSkills
      &headSkills, HeadEquipment &headEquipment);    
};

#endif
