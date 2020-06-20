#include <iostream>
#include <sstream>
#include <cassert>
#include "server/GameServer.h"

int main() {
  char mapPath[] = "client/assets/map/pindonga3.json";
  char port[] = "7777";
  GameServer game(port, mapPath);
  game.start();

  return 0;
}
