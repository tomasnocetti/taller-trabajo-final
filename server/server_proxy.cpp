#include "server_proxy.h"

#include <iostream>

ServerProxy::ServerProxy(GameServer &game): 
  game(game), continuePlaying(true){}

void ServerProxy::run(){
  while (continuePlaying){
    player.create();
    game.addActivePlayer(player);
    player.getPlayerCoordintates();
    stopPlaying();
  }
}

void ServerProxy::stopPlaying(){
  continuePlaying = false;
}

ServerProxy::~ServerProxy(){}
