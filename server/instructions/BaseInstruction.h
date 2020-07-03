#ifndef BASE_INSTRUCTION_H
#define BASE_INSTRUCTION_H

#include "../../common/BlockingQueue.h"
#include <string>
#include <memory>
#include <algorithm>  

class GameModel;

class Instruction {
  public:
    Instruction() : valid(true) {}
    Instruction(const Instruction&) = delete;
    Instruction& operator=(const Instruction&) = delete;
    Instruction&& operator=(Instruction&& other) = delete;
    virtual void run(GameModel& game) = 0;
    virtual ~Instruction() = default;
    bool isValid(const std::string& s){
      return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }

  protected: 
    bool valid;
};
using InstructionBQ = BlockingQueue<std::unique_ptr<Instruction>>;

#include "../GameModel.h"
#endif
