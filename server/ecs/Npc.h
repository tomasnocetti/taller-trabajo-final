#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include "../../DataDefinitions.h"
#include "../GameModel.h"

class NPC : public LiveEntity {
  public:
    NPC(EnemyData npcData, SkillsData skills, size_t level);
    ~NPC();
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;
    bool checkCollision(Entity& otherEntity) const override;
    bool checkInRange(Entity& otherEntity, double distance) const override;
    int attack(LiveEntity &entity, int xCoord, int yCoord) override;
    int deathDrop();

  private:
    size_t id;
    NPCClass type;
    MovementData movement;
    unsigned int seed;
    friend class GameModel;
};

#endif
