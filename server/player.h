#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <string>
#include <vector>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

typedef struct Inventory{
  std::string helmet;
}inventory_t;

typedef struct PlayerData{
  uint32_t manaPoints;
  uint32_t gold;
  std::string type;
  uint32_t accountNumber;
  uint32_t level;
  entityData_t data; 
  inventory_t inventory;
}playerData_t;

class Player : public Entity{
private:
  playerData_t playerData;
public:
  Player();
  void create();
  void move(uint32_t direction);
  void setPlayerDataToCreateNewPlayer();
  void setPlayerCoordinates(uint32_t x, uint32_t y);
  uint32_t getXCoordinate();
  uint32_t getYCoordinate();
  void revive();
  std::vector<int> estimateCoordintates(uint32_t direction);
  ~Player();
};

#endif
