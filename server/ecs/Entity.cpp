#include "Entity.h"
#include <math.h>   

Entity::Entity(PositionData& p) : position(p) {}

bool Entity::checkCollision(Entity& otherEntity) const{
  PositionData& otherp = otherEntity.position;

  return position.x + position.w >= otherp.x &&
		otherp.x + otherp.w >= position.x &&
		position.y + position.h >= otherp.y &&
		otherp.y + otherp.h >= position.y;
}

bool Entity::checkInRange(Entity& otherEntity, double distance) const{
  PositionData& otherp = otherEntity.position;

  double xCenter = position.x + position.w / 2;
  double yCenter = position.y + position.h / 2;

  double otherXCenter = otherp.x + otherp.w / 2;
  double otherYCenter = otherp.y + otherp.h / 2;

  double realDist = sqrt(
    pow(otherXCenter - xCenter, 2) + pow(otherYCenter - yCenter, 2));

  return ((realDist - distance) <= 0);
}

LiveEntity::LiveEntity(PositionData& p, HealthAndManaData& h) :
  Entity(p),
  health(h) {}
