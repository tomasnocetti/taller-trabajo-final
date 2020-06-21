#ifndef BASE_INSTRUCTION_H
#define BASE_INSTRUCTION_H

#include "../../common/BlockingQueue.h"
#include <string>
#include <memory>

class GameModel;

class Instruction {
  public:
    Instruction() = default;
    Instruction(const Instruction&) = delete;
    Instruction& operator=(const Instruction&) = delete;
    Instruction&& operator=(Instruction&& other) = delete;
    virtual void run(GameModel& game) = 0;
    virtual ~Instruction() = default;
};
using InstructionBQ = BlockingQueue<std::unique_ptr<Instruction>>;

#include "../GameModel.h"
#endif
