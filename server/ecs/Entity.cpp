#include "Entity.h"
#include <math.h>
#include <iostream>

Entity::Entity(PositionData& p) : position(p) {}

bool Entity::checkPositionCollision(
  const PositionData& p1, const PositionData&p2) {
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

MovementData Entity::getPositionDirection(
  const PositionData& from, const PositionData& to) {
  MovementData a = {0, 0};
  int dirX = to.x - from.x;
  int dirY = to.y - from.y;

  if (abs(dirX) > abs(dirY)) {
    a.xDir = dirX >= 0 ? 1 : -1;
  } else {
    a.yDir = dirY >= 0 ? 1 : -1;
  }
  return a;
}

bool Entity::checkCollision(Entity& otherEntity) const{
  PositionData& otherp = otherEntity.position;

  return Entity::checkPositionCollision(position, otherp);
}

bool Entity::checkInRange(Entity& otherEntity, double distance) const{
  return Entity::checkPositionInRange(position, otherEntity.position, distance);
}

double Entity::getPositionDistance(
  const Entity &entity){
    return Entity::getPositionDistance(position, entity.position);
}

Entity::~Entity(){}

LiveEntity::LiveEntity(PositionData& p, HealthAndManaData& h, SkillsData &s,
  size_t level) :
    Entity(p),
    level(level),
    health(h),
    skills(s) {}

void LiveEntity::rcvDamage(int &damage){
  health.currentHP -= damage;
}
