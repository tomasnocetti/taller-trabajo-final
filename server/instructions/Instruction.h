#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <memory>
#include "../../common/BlockingQueue.h"

class ClientProxy;
class Instruction;
using InstructionBQ = BlockingQueue<std::unique_ptr<Instruction>>;

#include "../GameModel.h"
#include "../ClientProxy.h"

class Instruction {
  public:
    Instruction() = default;
    Instruction(const Instruction&) = delete;
    Instruction& operator=(const Instruction&) = delete;
    Instruction&& operator=(Instruction&& other) = delete;
    virtual void run(GameModel& game) = 0;
    virtual ~Instruction() = default;
};

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

class CloseInstruction: public Instruction {
  public:
    explicit CloseInstruction(size_t id);
    CloseInstruction(const CloseInstruction&) = delete;
    CloseInstruction& operator=(const CloseInstruction&) = delete;
    CloseInstruction&& operator=(CloseInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};

class StopMovementInstruction: public Instruction {
  public:
    explicit StopMovementInstruction(size_t id);
    StopMovementInstruction(const StopMovementInstruction&) = delete;
    StopMovementInstruction& operator=(const StopMovementInstruction&) = delete;
    StopMovementInstruction&& operator=(StopMovementInstruction&& other) 
      = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
};


#endif
