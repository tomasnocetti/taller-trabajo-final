#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include "../ClientProxy.h"
#include "../GameModel.h"

class ClientProxy;

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
    explicit MoveInstruction(size_t id);
    MoveInstruction(const MoveInstruction&) = delete;
    MoveInstruction& operator=(const MoveInstruction&) = delete;
    MoveInstruction&& operator=(MoveInstruction&& other) = delete;
    void run(GameModel& game) override;

  private:
    size_t playerId;
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

#endif
