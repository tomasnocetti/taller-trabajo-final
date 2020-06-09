#include "game_server.h"
#include <memory>
#include <iostream>

GameServer::GameServer(){}

GameServer::~GameServer(){}

void GameServer::run(){
  int i = 0;
  while (i < 2){
    acceptPlayer();
    i++;
  }
}

void GameServer::acceptPlayer(){
  std::unique_ptr<ServerProxy> p(new ServerProxy(*this));
  p->run();
} 

void GameServer::addActivePlayer(Player player){
  activePlayers.push_back(player);
}
