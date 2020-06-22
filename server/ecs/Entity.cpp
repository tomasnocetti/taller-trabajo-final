#include "Entity.h"
#include <math.h>

Entity::Entity(PositionData& p) : position(p) {}

bool Entity::checkPositionCollision(const PositionData& p1, const PositionData&p2) {
  return p1.x + p1.w >= p2.x &&
		p2.x + p2.w >= p1.x &&
		p1.y + p1.h >= p2.y &&
		p2.y + p2.h >= p1.y;
}

bool Entity::checkPositionInRange(
  const PositionData& p1,
  const PositionData& p2,
  double distance) {
  double realDist = Entity::getPositionDistance(p1, p2);

  return ((realDist - distance) <= 0);
}

double Entity::getPositionDistance(
  const PositionData& p1,
  const PositionData& p2) {
  double xCenter = p1.x + p1.w / 2;
  double yCenter = p1.y + p1.h / 2;

  double otherXCenter = p2.x + p2.w / 2;
  double otherYCenter = p2.y + p2.h / 2;

  return sqrt(
    pow(otherXCenter - xCenter, 2) + pow(otherYCenter - yCenter, 2));
}

bool Entity::checkCollision(Entity& otherEntity) const{
  PositionData& otherp = otherEntity.position;

  return Entity::checkPositionCollision(position, otherp);
}

bool Entity::checkInRange(Entity& otherEntity, double distance) const{
  return Entity::checkPositionInRange(position, otherEntity.position, distance);
}

LiveEntity::LiveEntity(PositionData& p, HealthAndManaData& h) :
  Entity(p),
  health(h) {}
