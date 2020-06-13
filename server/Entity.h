#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <../DataDefinitions.h>


/**
 * @brief Se define entidad como un objeto que participa en el juego 
 * de alguna manera, no necesariamente un NPC o un jugador.
 */
class Entity {
  private:
    PositionData position;
  public:
    bool checkCollision(Entity& otherEntity) const;
};

/**
 * @brief Se define a una entidad viva como un objeto que participa en el juego
 * y que tiene un estado de salud.
 */
class LiveEntity: public Entity {
  private:
    HealthData health;
  public:
    void move();
}

#endif
