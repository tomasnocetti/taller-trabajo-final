#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

Player::Player(MainPlayerData playerData, size_t id) :
  LiveEntity(playerData.position, playerData.points),
  id(id),
  root(playerData.rootd),
  gold(playerData.gold),
  level(playerData.level) {}

Player::~Player(){}


void Player::move(std::string x, std::string y){
  position.x = stoi(x);
  position.y = stoi(y);
}

// void Player::setPlayerDataToCreateNewPlayer(){
  /*
  playerData.manaPoints = 0;
  playerData.gold = 0;
  playerData.type = "Default"; // aca va a ir un  tipo de raza
  playerData.accountNumber = 0; // hay que pensar como inicializarla
  playerData.level = 1; // uno o cero?
  playerData.inventory.helmet = "inicializar con casco?";
  playerData.data.isDead = false;
  playerData.data.lifePoints = MAX_LIFE_LEVEL_1;
  */
// }

// void Player::revive(){}

// std::vector<int> Player::estimateCoordintates(uint32_t direction){
//   std::vector<int> coordinates = {0,0};
//   switch (direction)
//   {
//   // case RIGHT: coordinates[0] = getXCoordinate() + 5;
//   // break;
//   default:
//     break;
//   }
//   return coordinates;
// }
