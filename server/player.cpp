#include "player.h"

#define MAX_LIFE_LEVEL_1 100

Player::Player(){}

Player::~Player(){}

void Player::create(){
  setPlayerDataToCreateNewPlayer(this->playerData);
}

void Player::move(playerData_t playerData, uint32_t direction){}

void Player::setPlayerDataToCreateNewPlayer(playerData_t playerData){
  playerData.manaPoints = 0;
  playerData.gold = 0;
  playerData.type = "Default"; // aca va a ir un  tipo de raza
  playerData.accountNumber = 0; // hay que pensar como inicializarla
  playerData.level = 1; // uno o cero?
  playerData.inventory.helmet = "inicializar con casco?";
  playerData.data.isDead = false;
  playerData.data.lifePoints = MAX_LIFE_LEVEL_1;
  setPlayerCoordinates(playerData, 0, 0);
}

void Player::setPlayerCoordinates(playerData_t playerData, uint32_t x, 
  uint32_t y){
  playerData.data.x = x;
  playerData.data.y = y; 
}
