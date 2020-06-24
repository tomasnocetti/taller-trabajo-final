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

void Player::attack(LiveEntity &entity, int xCoord, int yCoord){
  PositionData attackZoneData = {
    xCoord,
    yCoord,
    ATTACK_ZONE_WIDTH,
    ATTACK_ZONE_HEIGHT};
  Entity attackZone(attackZoneData);
  
  bool attackSuccess = entity.checkCollision(attackZone);
  
  if (!attackSuccess) return;

  entity.rcvDamage();
}
