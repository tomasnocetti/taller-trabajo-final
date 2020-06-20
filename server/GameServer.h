#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "instructions/Instruction.h"
#include "responses/Response.h"
#include "services/MapParser.h"
#include "ClientAcceptor.h"
#include "GameCron.h"
#include "GameModel.h"

class ClientProxy;

class GameServer{
  private:
    bool running;
    InstructionBQ instructionQueue;
    GameModel game;
    GameCron cron;
    MapParser m;
  public:
    explicit GameServer(std::string& mapPath);
    ~GameServer();
    GameServer(const GameServer&) = delete;
    GameServer& operator=(const GameServer&) = delete;
    void init();
    void start();
    void close();
};

#endif
