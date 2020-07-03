#include "ServerRun.h"
#include "GameServer.h"
#include "GameConfig.h"
#include <iostream>
#include <string>

#define FINISH_COMMAND "q"

void waitToFinish() {
  std::string command_string;
  while (!std::cin.eof()) {
    std::getline(std::cin, command_string);
    if (command_string == FINISH_COMMAND) break;
  }
}

void serverRun(char *port, char *configFilePath) {
  GC::load(configFilePath);
  GameServer game(port);

  game.start();
  waitToFinish();
  game.stop();

}
