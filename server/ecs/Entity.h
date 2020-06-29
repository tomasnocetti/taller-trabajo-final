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
    friend class GameModel;
    PositionData position;
  public:
    explicit Entity(PositionData& p);
    virtual ~Entity();
    static bool checkPositionCollision(
      const PositionData& p1, const PositionData&p2);
    static double getPositionDistance(
      const PositionData& p1, const PositionData&p2);
    static bool checkPositionInRange(
      const PositionData& p1,
      const PositionData& p2,
      double distance);
    static MovementData getPositionDirection(
      const PositionData& from, const PositionData& to);
    virtual bool checkCollision(Entity& otherEntity) const;
    virtual bool checkInRange(Entity& otherEntity, double distance) const;
    virtual double getPositionDistance(const Entity& entity);
};

/**
 * @brief Se define a una entidad viva como un objeto que participa en el juego
 * y que tiene un estado de salud.
 */
class LiveEntity: public Entity {
  protected:
    friend class Player;
    friend class NPC;
    friend class GameModel;
    size_t level;
    HealthAndManaData health;
    SkillsData skills;
    size_t id;
  public:
    LiveEntity(PositionData& p, HealthAndManaData& h, SkillsData &s, 
      size_t level, size_t id);
    virtual void rcvDamage(int &damage);
    virtual bool attack(LiveEntity &entity, int xCoord, int yCoord) = 0;
};

#endif
