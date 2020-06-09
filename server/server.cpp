#include <iostream>
#include <sstream>
#include <cassert>
#include <msgpack.hpp>
#include "file_manager.h"
#include "game_server.h" 

int main(){
  GameServer game;
  game.run();
  return 0;
}

/*
  FileManager fileManager;
  Data dataPlayerFerfa = {0, 1000, 300};
  Data dataPlayerTomi = {100, 1000, 30000};
  Data dataPlayerLauti = {0, 1000, 0};
  Data dataPlayerWalter = {0, 0, 0};
  fileManager.create("Ferfa");
  fileManager.create("Tomi");
  fileManager.create("Tomi");
  fileManager.create("Ferfa");
  fileManager.create("Lauti");
  fileManager.create("Walter");
  fileManager.loadPlayerData("Ferfa", dataPlayerFerfa);
  fileManager.loadPlayerData("Tomi", dataPlayerTomi);
  fileManager.loadPlayerData("Lauti", dataPlayerLauti);
  fileManager.loadPlayerData("Walter", dataPlayerWalter);
  fileManager.downloadPlayerData("Ferfa");
  fileManager.downloadPlayerData("Lauti");
  fileManager.downloadPlayerData("Tomi");
  fileManager.downloadPlayerData("Walter");
*/
