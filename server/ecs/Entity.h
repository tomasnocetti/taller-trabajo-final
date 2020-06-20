#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

#include "../../DataDefinitions.h"

/**
 * @brief Se define entidad como un objeto que participa en el juego 
 * de alguna manera, no necesariamente un NPC o un jugador.
 */
class Entity {
  protected:
    PositionData position;
  public:
    explicit Entity(PositionData& p);
    bool checkCollision(Entity& otherEntity) const;
    bool checkInRange(Entity& otherEntity, double distance) const;
};

/**
 * @brief Se define a una entidad viva como un objeto que participa en el juego
 * y que tiene un estado de salud.
 */
class LiveEntity: public Entity {
  protected:
    HealthAndManaData health;
  public:
    LiveEntity(PositionData& p, HealthAndManaData& h);
    void move();
};

#endif
