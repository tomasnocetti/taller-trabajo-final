#include "ServerRun.h"
#include "GameServer.h"
#include "GameConfig.h"
#include "services/FileManager.h"
#include <iostream>
#include <string>

#define FINISH_COMMAND "q"
#define INIT_MSG " Argentum server esta corriendo. "\
  "Para finalizar presione 'q'."
#define END_MSG " Argentum server se esta cerrando.\n " \
  "Todos los jugadores deben finalizar sus partidas."

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
  std::cout << INIT_MSG << std::endl;
  waitToFinish();
  std::cout << END_MSG << std::endl;
  game.stop();
}
