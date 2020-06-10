#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include "player.h"
#include "server_proxy.h"
#include <iostream>
#include <memory>

class ServerProxy;

class GameServer{
private:
  std::vector<std::unique_ptr<Player>> activePlayers; 
public:
  GameServer();
  ~GameServer();
  void run();
  void addActivePlayer(Player &player);
  bool askForCoordinates(uint32_t x, uint32_t y);
  void acceptPlayer();
};

#endif
