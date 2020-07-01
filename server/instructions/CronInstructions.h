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
    NPCSetCoordsInstruction(size_t id, int xPos, int yPos);
    NPCSetCoordsInstruction(
      const NPCSetCoordsInstruction&) = delete;
    NPCSetCoordsInstruction& operator=(
      const NPCSetCoordsInstruction&) = delete;
    NPCSetCoordsInstruction&& operator=(
      NPCSetCoordsInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t npcId;
    int xPos;
    int yPos;
};

class NPCAttackInstruction: public Instruction {
  public:
    NPCAttackInstruction(size_t id, int xPos, int yPos);
    NPCAttackInstruction(
      const NPCAttackInstruction&) = delete;
    NPCAttackInstruction& operator=(
      const NPCAttackInstruction&) = delete;
    NPCAttackInstruction&& operator=(
      NPCAttackInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t npcId;
    int xPos;
    int yPos;
};

class NPCRespawnInstruction: public Instruction {
  public:
    explicit NPCRespawnInstruction(size_t id);
    NPCRespawnInstruction(
      const NPCRespawnInstruction&) = delete;
    NPCRespawnInstruction& operator=(
      const NPCRespawnInstruction&) = delete;
    NPCRespawnInstruction&& operator=(
      NPCRespawnInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t npcId;
};

class PlayerResurrecctionInstruction : public Instruction {
  public:
    explicit PlayerResurrecctionInstruction(size_t id);
    PlayerResurrecctionInstruction(
      const PlayerResurrecctionInstruction&) = delete;
    PlayerResurrecctionInstruction& operator=(
      const PlayerResurrecctionInstruction&) = delete;
    PlayerResurrecctionInstruction&& operator=(
      PlayerResurrecctionInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class PlayerIncreaseHealthInstruction : public Instruction {
  public:
    explicit PlayerIncreaseHealthInstruction(size_t id);
    PlayerIncreaseHealthInstruction(
      const PlayerIncreaseHealthInstruction&) = delete;
    PlayerIncreaseHealthInstruction& operator=(
      const PlayerIncreaseHealthInstruction&) = delete;
    PlayerIncreaseHealthInstruction&& operator=(
      PlayerIncreaseHealthInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class PlayerIncreaseManaInstruction : public Instruction {
  public:
    explicit PlayerIncreaseManaInstruction(size_t id);
    PlayerIncreaseManaInstruction(
      const PlayerIncreaseManaInstruction&) = delete;
    PlayerIncreaseManaInstruction& operator=(
      const PlayerIncreaseManaInstruction&) = delete;
    PlayerIncreaseManaInstruction&& operator=(
      PlayerIncreaseManaInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class IncreaseManaMeditationInstruction : public Instruction {
  public:
    explicit IncreaseManaMeditationInstruction(size_t id);
    IncreaseManaMeditationInstruction(
      const IncreaseManaMeditationInstruction&) = delete;
    IncreaseManaMeditationInstruction& operator=(
      const IncreaseManaMeditationInstruction&) = delete;
    IncreaseManaMeditationInstruction&& operator=(
      IncreaseManaMeditationInstruction&& other);
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

#endif
