#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "../DataDefinitions.h"
#include "BlockingQueue.h"

class ServerProxy;

class GameServer{
private:
  bool isClose;
  std::vector<std::unique_ptr<Player>> activePlayers; 
public:
  BlockingQueue updateModel;
  GameServer();
  ~GameServer();
  void init();
  void start();
  void handleInstruction(InstructionData &instruction);
  void close();
  void addActivePlayer(Player &player);
  void acceptPlayer();
};

#endif
