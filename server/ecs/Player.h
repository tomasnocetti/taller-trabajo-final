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
    LevelAndExperienceData levelAndExperience;
    PlayerRootData rootd;
    Inventory inventory;
    MovementData movement;
    EquipmentData equipment;
    Equations gameEquations;
    friend class GameModel;

  public:
    Player(MainPlayerData playerData, size_t id);
    ~Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    void attack(LiveEntity &entity, int xCoord, int yCoord);
    static std::unique_ptr<Player> createPlayer(
      size_t id, 
      std::string nick, 
      PlayerRootData root);
    static void setClassSkills(SkillsData &skills, PlayerRootData &root);
    static void setRaceSkills(SkillsData &skills, PlayerRootData &root);  
    static void setInitEquipment(EquipmentData &equipment, 
      PlayerRootData &root);      
};

#endif
