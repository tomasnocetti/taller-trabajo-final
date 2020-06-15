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
#include "GameModel.h"

class ServerProxy;

using InstructionDataBQ = BlockingQueue<InstructionData>;
using UpDateClientsBQ = FixedBlockingQueue<PlayerGameModelData>;

class GameServer{
  private: 
    bool isClose;
    InstructionDataBQ instructionQueue;
    ActivePlayers activePlayers;
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
