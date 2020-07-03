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

void Banker::deposit(Player &player) {}

void Banker::withdraw(Player &player) {}

void Banker::depositGold(Player &player, size_t amount) {
  player.depositGold(amount);
}

void Banker::withDrawGold(Player &player, size_t amount) {}
