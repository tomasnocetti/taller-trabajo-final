#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../../DataDefinitions.h"
#include "../GameModel.h"
#include <string>

class Player : public LiveEntity{
  private:
    std::string nick;
    size_t id;
    size_t gold;
    LevelExperienceAndSkillsData levelExperienceSkills;
    PlayerRootData rootd;
    Inventory inventory;
    HealthAndManaData points;
    PositionData position;
    MovementData movement;
    EquipmentData equipment;
    friend class GameModel;

  public:
    Player(MainPlayerData playerData, size_t id);
    ~Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    void attack(LiveEntity &entity, int xCoord, int yCoord);
};

#endif
