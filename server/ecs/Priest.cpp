#include "Priest.h"

#include "../GameConfig.h"
#include "../services/ChatManager.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

Priest::Priest(PositionData position) :
  Entity(position) {
  const GlobalConfig& c = GC::get();

  // Preparo items de manera legible
  for (unsigned int i = 0; i < c.priestItems.size(); i++) {
    std::stringstream ss;
    const TraderItem& traderItem = c.priestItems[i];
    const std::unique_ptr<Item> &item = c.items.at(traderItem.itemId);

    ss << "   " << i+1 << ". " << item->name << " <" << traderItem.value << ">";
    readableItems.push_back(ss.str());
  }
}

void Priest::sell(size_t option, Player &p) {
  const GlobalConfig& c = GC::get();
  if (option > c.priestItems.size()) {
    ChatManager::invalidOption(p.chat);
    return;
  }

  const TraderItem& traderItem = c.priestItems[option - 1];
  p.buy(traderItem.value, traderItem.itemId);
}

std::vector<std::string>& Priest::getItemsList() {
  return readableItems;
}

size_t Priest::idGenerator = 0;

size_t Priest::getNewId(){
  Priest::idGenerator ++;
  return Priest::idGenerator;
}

void Priest::listItems(Player &player){
  std::vector<std::string> items;
  items = getItemsList();
  for (std::string &str : items){
    player.sendMessage(NORMAL, str);
  }
}
