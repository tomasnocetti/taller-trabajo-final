#include "game_server.h"
#include <utility>

GameServer::GameServer(){}

GameServer::~GameServer(){}

void GameServer::run(){
  int i = 0;

  while (i < 2){
    acceptPlayer();
    i++;
  }

  std::cout << activePlayers.at(0)->getXCoordinate() << std::endl;
}

void GameServer::acceptPlayer(){
  std::unique_ptr<ServerProxy> p(new ServerProxy(*this));
  p->run();
}

void GameServer::addActivePlayer(Player &player){
  std::unique_ptr<Player> p(&player);
  activePlayers.push_back(std::move(p));
}

bool GameServer::askForCoordinates(uint32_t x, uint32_t y){
  return true;
}
