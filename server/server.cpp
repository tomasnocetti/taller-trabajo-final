#include <iostream>
#include <sstream>
#include <cassert>
#include <msgpack.hpp>
#include "file_manager.h"
 
int main(){
  char *file1 = "playersIndex.txt";
  FileManager fileManager(file1);
  Data dataPlayerFerfa = {100, 1000, 300};
  Data dataPlayerTomi = {100, 1000, 300};
  Data dataPlayerLauti = {100, 1000, 300};
  fileManager.create("Ferfa");
  fileManager.create("Tomi");
  fileManager.create("Tomi");
  fileManager.create("Ferfa");
  fileManager.create("Lauti");
  fileManager.loadPlayerData("Ferfa", dataPlayerFerfa);
  fileManager.loadPlayerData("Tomi", dataPlayerTomi);
  fileManager.loadPlayerData("Lauti", dataPlayerLauti);
  fileManager.downloadPlayerData("Ferfa");
  fileManager.downloadPlayerData("Lauti");
  fileManager.downloadPlayerData("Tomi");
  return 0;
}
