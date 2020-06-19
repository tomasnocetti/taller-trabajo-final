#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Player.h"
#include "../DataDefinitions.h"
#include "instructions/Instruction.h"
#include "responses/Response.h"
#include "GameModel.h"
#include "ClientAcceptor.h"

class ClientProxy;
class ClientAcceptor;

class GameServer{
  private:
    bool running;
    InstructionBQ instructionQueue;
    GameModel game;
    ClientAcceptor clientAcceptor;
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
