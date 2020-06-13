#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <string>
#include <vector>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

class Player : public Entity{
  private:
    PlayerDataT playerData;
  public:
    Player();
    ~Player();
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    void create();
    void move(uint32_t direction);
    void setPlayerDataToCreateNewPlayer();
    void setPlayerCoordinates(uint32_t x, uint32_t y);
    uint32_t getXCoordinate();
    uint32_t getYCoordinate();
    void revive();
    std::vector<int> estimateCoordintates(uint32_t direction);
};

#endif
