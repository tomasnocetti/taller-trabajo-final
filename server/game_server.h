#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <vector>
#include <string>
#include "player.h"
#include "server_proxy.h"

class ServerProxy;

class GameServer{
private:
  std::vector<Player> activePlayers; 
public:
  GameServer();
  ~GameServer();
  void run();
  void addActivePlayer(Player player);
  void acceptPlayer();
};

#endif
