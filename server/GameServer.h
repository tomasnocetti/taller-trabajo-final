#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Player.h"
#include "../DataDefinitions.h"
#include "../common/BlockingQueue.h"
#include "instructions/Instruction.h"
#include "GameModel.h"

class ClientProxy;

using InstructionBQ = BlockingQueue<std::unique_ptr<Instruction>>;
using UpdateClientsBQ = FixedBlockingQueue<PlayerGameModelData>;

class GameServer{
  private:
    bool running;
    InstructionBQ instructionQueue;
    GameModel game;
  public:
    GameServer();
    ~GameServer();
    GameServer(const GameServer&) = delete;
    GameServer& operator=(const GameServer&) = delete;
    void init();
    void start();
    void close();
};

#endif
