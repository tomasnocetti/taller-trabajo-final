#ifndef CLIENT_INSTRUCTION_H
#define CLIENT_INSTRUCTION_H

#include "BaseInstruction.h"
#include "../ClientProxy.h"
#include <string>

class Instruction;
class ClientProxy;

class MoveInstruction: public Instruction {
  public:
    MoveInstruction(size_t id, std::string xDir, std::string yDir);
    MoveInstruction(const MoveInstruction&) = delete;
    MoveInstruction& operator=(const MoveInstruction&) = delete;
    MoveInstruction&& operator=(MoveInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    std::string xDir;
    std::string yDir;
};

class AuthInstruction: public Instruction {
  public:
    explicit AuthInstruction(ClientProxy& client, std::string nick);
    AuthInstruction(const AuthInstruction&) = delete;
    AuthInstruction& operator=(const AuthInstruction&) = delete;
    AuthInstruction&& operator=(AuthInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    ClientProxy& client;
    std::string nick;
};

class CloseInstruction : public Instruction {
  public:
    explicit CloseInstruction(size_t id);
    CloseInstruction(const CloseInstruction&) = delete;
    CloseInstruction& operator=(const CloseInstruction&) = delete;
    CloseInstruction&& operator=(CloseInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class StopMovementInstruction : public Instruction {
  public:
    explicit StopMovementInstruction(size_t id);
    StopMovementInstruction(const StopMovementInstruction&) = delete;
    StopMovementInstruction& operator=(const StopMovementInstruction&) 
      = delete;
    StopMovementInstruction&& operator=(StopMovementInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class AttackInstrucion : public Instruction {
  public:
    AttackInstrucion(size_t id, std::string xPos, std::string yPos);
    AttackInstrucion(const AttackInstrucion&) = delete;
    AttackInstrucion& operator=(const AttackInstrucion&) 
      = delete;
    AttackInstrucion&& operator=(AttackInstrucion&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    int xPos;
    int yPos;
};

class EquipInstruction : public Instruction {
  public:
    EquipInstruction(size_t id, std::string inventoryPosition);
    EquipInstruction(const EquipInstruction&) = delete;
    EquipInstruction& operator=(const EquipInstruction&) 
      = delete;
    EquipInstruction&& operator=(EquipInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
    size_t inventoryPosition;
};

#endif
