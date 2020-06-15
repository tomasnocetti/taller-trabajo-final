#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

Player::Player(MainPlayerData playerData, size_t id) :  id(id),
  root(playerData.root), inventory(playerData.inventory), 
  health(playerData.health), position(playerData.position),
  manaPoints(playerData.manaPoints), gold(playerData.gold), 
  level(playerData.level) {}

Player::~Player(){}

void Player::move(std::string x, std::string y){
  position.x = stoi(x);
  position.y = stoi(y);
}
