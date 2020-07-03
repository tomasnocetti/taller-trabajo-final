#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "instructions/Instruction.h"
#include "responses/Response.h"
#include "ClientAcceptor.h"
#include "GameCron.h"
#include "GameModel.h"
#include "ClientAcceptor.h"

class ClientProxy;

class GameServer : public Thread{
  private:
    bool running;
    InstructionBQ instructionQueue;
    GameCron cron;
    GameModel game;
    ClientAcceptor clientAcceptor;
  public:
    explicit GameServer(char* port);
    ~GameServer();
    GameServer(const GameServer&) = delete;
    GameServer& operator=(const GameServer&) = delete;
    void init();
    void run();
    void stop();
};

#endif
