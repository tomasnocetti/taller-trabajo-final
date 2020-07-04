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

void Banker::listItems(Player &player){
  const GlobalConfig& c = GC::get();

  int i = 1;
  for (InventoryElementData &it : player.itemsInBank){
    const InventoryElementData& bankItem = it;
    const std::unique_ptr<Item> &item = c.items.at(bankItem.itemId);

    player.sendMessage(NORMAL, std::to_string(i) + ". " + item->name + 
      " : " + std::to_string(it.amount));
    
    i++;
  }
  player.sendMessage(NORMAL, "Cantidad de oro disponible: " + 
    std::to_string(player.goldInBank));
}

void Banker::deposit(Player &player, size_t inventoryPos) {
  player.depositItem(inventoryPos);
}

void Banker::depositGold(Player &player, size_t amount) {
  player.depositGold(amount);
}

void Banker::withdraw(Player &player, size_t inventoryPos) {
  player.withdrawItem(inventoryPos);
}

void Banker::withDrawGold(Player &player, size_t amount) {
  player.withdrawGold(amount);
}
