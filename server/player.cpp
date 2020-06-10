#include "player.h"
#include <iostream>
#include <vector>

#define MAX_LIFE_LEVEL_1 100

Player::Player(){}

Player::~Player(){}

void Player::create(){  
  setPlayerDataToCreateNewPlayer();
}

void Player::move(uint32_t direction){
  playerData.data.x += 5;
  std::cout << playerData.data.x << std::endl;
  std::cout << playerData.data.y << std::endl;
}

void Player::setPlayerDataToCreateNewPlayer(){
  playerData.manaPoints = 0;
  playerData.gold = 0;
  playerData.type = "Default"; // aca va a ir un  tipo de raza
  playerData.accountNumber = 0; // hay que pensar como inicializarla
  playerData.level = 1; // uno o cero?
  playerData.inventory.helmet = "inicializar con casco?";
  playerData.data.isDead = false;
  playerData.data.lifePoints = MAX_LIFE_LEVEL_1;
  playerData.data.x = 0;
  playerData.data.y = 0;
}

void Player::setPlayerCoordinates(uint32_t x, uint32_t y){
  playerData.data.x += x;
  playerData.data.y += y; 
}

uint32_t Player::getXCoordinate(){
  return playerData.data.x;
}

uint32_t Player::getYCoordinate(){
  return playerData.data.y;
}

void Player::revive(){}

std::vector<int> Player::estimateCoordintates(uint32_t direction){
  std::vector<int> coordinates = {0,0};
  switch (direction)
  {
  case RIGHT: coordinates[0] = getXCoordinate() + 5;
  break;
  default:
    break;
  }
  return coordinates;
}
