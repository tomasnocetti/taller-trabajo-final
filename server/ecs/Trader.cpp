#include "Trader.h"

#include "../GameConfig.h"
#include "../services/ChatManager.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

Trader::Trader(PositionData position) :
  Entity(position) {
  const GlobalConfig& c = GC::get();

  // Preparo items de manera legible
  for (unsigned int i = 0; i < c.traderItems.size(); i++) {
    std::stringstream ss;
    const TraderItem& traderItem = c.traderItems[i];
    const std::unique_ptr<Item> &item = c.items.at(traderItem.itemId);

    ss << "   " << i+1 << ". " << item->name << " <" << traderItem.value << ">";
    readableItems.push_back(ss.str());
  }
}

void Trader::buy(Player& p, size_t inventoryPos) {
  std::cout << "Comprando elemento: " << p.inventory[inventoryPos].itemId 
    << std::endl;
}

void Trader::sell(size_t option, Player &p) {
  const GlobalConfig& c = GC::get();
  if (option >= c.traderItems.size()) {
    ChatManager::invalidOption(p.chat);
  }

  const TraderItem& traderItem = c.traderItems[option];
  p.buy(traderItem.value, traderItem.itemId);
}

std::vector<std::string>& Trader::getItemsList() {
  std::cout << "ITEMS LIST" << std::endl;
  return readableItems;
}

size_t Trader::idGenerator = 0;

size_t Trader::getNewId(){
  Trader::idGenerator ++;
  return Trader::idGenerator;
}

void Trader::listItems(Player &player){
  std::vector<std::string> items;
  items = getItemsList();
  for (std::string &str : items){
    player.sendMessage(NORMAL, str);
  }
}
