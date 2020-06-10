#ifndef SERVER_PROXY_H
#define SERVER_PROXY_H

#include "GameServer.h"
#include "Player.h"
#include "BlockingQueue.h"

class GameServer;

class ServerProxy{
private:
  BlockingQueue &updateModel;
  Player player;
  bool continuePlaying;
public:
  explicit ServerProxy(BlockingQueue &updateModel);
  void run();
  void stopPlaying();
  void movePlayer(uint32_t direction);
  ~ServerProxy();
};

#endif
