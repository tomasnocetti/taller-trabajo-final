#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "../DataDefinitions.h"
#include "BlockingQueue.h"

class ServerProxy;

using InstructionDataBQ = BlockingQueue<InstructionData>;

class GameServer{
private:
  bool isClose;
  std::vector<std::unique_ptr<Player>> activePlayers; 
public:
  InstructionDataBQ updateModel;
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
