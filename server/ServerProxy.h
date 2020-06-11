#ifndef SERVER_PROXY_H
#define SERVER_PROXY_H

#include "GameServer.h"
#include "Player.h"
#include "BlockingQueue.h"

class GameServer;

class ServerProxy{
private:
  InstructionDataBQ &updateModel;
  Player player;
  bool continuePlaying;
public:
  explicit ServerProxy(InstructionDataBQ &updateModel);
  void run();
  void stopPlaying();
  void movePlayer(uint32_t direction);
  ~ServerProxy();
};

#endif
