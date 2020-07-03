#include "Banker.h"
#include "../GameConfig.h"
#include "../services/ChatManager.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

Banker::Banker(PositionData position) :
  Entity(position) {}

size_t Banker::idGenerator = 0;

size_t Banker::getNewId(){
  Banker::idGenerator ++;
  return Banker::idGenerator;
}

void Banker::listItems(Player &player){}
