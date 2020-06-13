#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Player.h"
#include "../DataDefinitions.h"
#include "../common/BlockingQueue.h"
#include "ActivePlayers.h"

class ServerProxy;

using InstructionDataBQ = BlockingQueue<InstructionData>;
using UpDateClientsBQ = FixedBlockingQueue<GameModelT>;

class GameServer{
  private: 
    bool isClose;
    InstructionDataBQ instructionQueue;
    ActivePlayers activePlayers;
    GameModelT gameModel;
  public:
    GameServer();
    ~GameServer();
    GameServer(const GameServer&) = delete;
    GameServer& operator=(const GameServer&) = delete;
    void init();
    void start();
    void handleInstruction(InstructionData &instruction);
    void close();
};

#endif
