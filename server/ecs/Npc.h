#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include "../../DataDefinitions.h"
#include "../GameModel.h"

class NPC : public LiveEntity {
  public:
    NPC(EnemyData npcData, SkillsData skills, size_t level);
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;
    bool checkCollision(Entity& otherEntity) const override;
    bool checkInRange(Entity& otherEntity, double distance) const override;
    bool attack(LiveEntity &entity, int xCoord, int yCoord) override;
    int drop(unsigned int &seed);
    static std::unique_ptr<NPC> createNPC(
      size_t id,
      PositionData position,
      size_t level,
      NPCClass npcType);
    static size_t getNewId();
  private:
    size_t id;
    NPCClass type;
    MovementData movement;
    static size_t idGenerator;
    friend class GameModel;
};

#endif
