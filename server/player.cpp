#include "player.h"
#include <iostream>

#define MAX_LIFE_LEVEL_1 100

Player::Player(){}

Player::~Player(){}

void Player::create(){
  setPlayerDataToCreateNewPlayer();
}

void Player::move(playerData_t playerData, uint32_t direction){}

void Player::setPlayerDataToCreateNewPlayer(){
  playerData.manaPoints = 0;
  playerData.gold = 0;
  playerData.type = "Default"; // aca va a ir un  tipo de raza
  playerData.accountNumber = 0; // hay que pensar como inicializarla
  playerData.level = 1; // uno o cero?
  playerData.inventory.helmet = "inicializar con casco?";
  playerData.data.isDead = false;
  playerData.data.lifePoints = MAX_LIFE_LEVEL_1;
  setPlayerCoordinates(0, 0);
}

void Player::setPlayerCoordinates(uint32_t x, uint32_t y){
  playerData.data.x = x;
  playerData.data.y = y; 
}

void Player::getPlayerCoordintates(){
  std::cout << playerData.data.x << std::endl;
  std::cout << playerData.data.y << std::endl;
}

int Player::getXCoordinate(){
  return playerData.data.x;
}

int Player::getYCoordinate(){
  return playerData.data.y;
}

void Player::revive(){}
