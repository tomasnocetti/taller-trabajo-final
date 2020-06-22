#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

Player::Player(MainPlayerData playerData, size_t id) :
  LiveEntity(playerData.position, playerData.points),
  id(id),
  root(playerData.rootd),
  inventory(playerData.inventory),
  movement(playerData.movement),
  gold(playerData.gold),
  level(playerData.level) {}

Player::~Player(){}
