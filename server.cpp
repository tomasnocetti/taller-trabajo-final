#include <iostream>
#include <sstream>
#include <cassert>
#include "server/GameServer.h" 

int main() {
  std::string mapPath = "client/assets/map/pindonga3.json";
  GameServer game(mapPath);
  game.start();
  
  return 0;
}
