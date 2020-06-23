#ifndef CRON_INSTRUCTION_H
#define CRON_INSTRUCTION_H

#include "BaseInstruction.h"

class PlayerSetCoordsInstruction: public Instruction {
  public:
    PlayerSetCoordsInstruction(size_t id, int x, int y);
    PlayerSetCoordsInstruction(
      const PlayerSetCoordsInstruction&) = delete;
    PlayerSetCoordsInstruction& operator=(
      const PlayerSetCoordsInstruction&) = delete;
    PlayerSetCoordsInstruction&& operator=(
      PlayerSetCoordsInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t playerId;
    int x;
    int y;
};

class NPCSetCoordsInstruction: public Instruction {
  public:
    NPCSetCoordsInstruction(size_t id, int x, int y);
    NPCSetCoordsInstruction(
      const NPCSetCoordsInstruction&) = delete;
    NPCSetCoordsInstruction& operator=(
      const NPCSetCoordsInstruction&) = delete;
    NPCSetCoordsInstruction&& operator=(
      NPCSetCoordsInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t npcId;
    int x;
    int y;
};

#endif
