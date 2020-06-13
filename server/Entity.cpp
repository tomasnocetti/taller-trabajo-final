#include "Entity.h"

bool Entity::checkCollision(Entity& otherEntity) const{
  PositionData& otherp = otherEntity.position;

  return position.x + position.w >= otherp.x &&
		otherp.x + otherp.w >= position.x &&
		position.y + position.h >= otherp.y &&
		otherp.y + otherp.h >= position.y;
}
