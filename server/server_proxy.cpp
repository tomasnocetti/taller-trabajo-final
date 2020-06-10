#include "server_proxy.h"

#include <iostream>
#include <vector>

ServerProxy::ServerProxy(GameServer &game): 
  game(game), continuePlaying(true){
    player.create();
}

void ServerProxy::run(){
  player.create();
  game.addActivePlayer(player);
  while (continuePlaying){
    movePlayer(RIGHT);
    stopPlaying();
  }
}

void ServerProxy::stopPlaying(){
  continuePlaying = false;
}

void ServerProxy::movePlayer(uint32_t direction){
  std::vector<int> coordinates = player.estimateCoordintates(direction);
  bool canMove = game.askForCoordinates(coordinates[0], coordinates[1]);
  if (canMove)
    player.move(direction);
}

ServerProxy::~ServerProxy(){}
