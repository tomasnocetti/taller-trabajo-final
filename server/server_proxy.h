#ifndef SERVER_PROXY_H
#define SERVER_PROXY_H

#include "game_server.h"
#include "player.h"

class GameServer;

class ServerProxy{
private:
  GameServer &game;
  Player player;
  bool continuePlaying;
public:
  explicit ServerProxy(GameServer &game);
  void run();
  void stopPlaying();
  void movePlayer(uint32_t direction);
  ~ServerProxy();
};

#endif
