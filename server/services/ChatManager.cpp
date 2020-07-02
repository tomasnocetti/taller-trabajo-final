#include "ChatManager.h"

#include "../GameConfig.h"

void ChatManager::initialMessage(ChatData &chat){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO, c.chatMessages.initialMsg});
}

void ChatManager::damageReceived(ChatData &chat, int damage){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({DANGER,
      c.chatMessages.damageRcvMsg + std::to_string(damage)});
}

void ChatManager::enemyDodgedTheAttack(ChatData &chat){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO, c.chatMessages.enemyDodgedAttack});
}

void ChatManager::attackDodged(ChatData &chat){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({SUCCESS, c.chatMessages.attackDodged});
}

void ChatManager::damageCaused(ChatData &chat, int damage){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({SUCCESS,
    c.chatMessages.damageCaused + std::to_string(damage)});
}

void ChatManager::insufficientFunds(ChatData &chat) {
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO,
    c.chatMessages.insufficientFunds});
}

void ChatManager::noInventorySpace(ChatData &chat) {
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO,
    c.chatMessages.noInventorySpace});
}

void ChatManager::invalidOption(ChatData &chat) {
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO,
    c.chatMessages.invalidOption});
}

void ChatManager::meditating(ChatData &chat){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO,
    c.chatMessages.meditating});  
}

void ChatManager::stopMeditating(ChatData &chat){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({INFO,
    c.chatMessages.stopMeditating});  
}

void ChatManager::inventoryIsFull(ChatData &chat){
  const GlobalConfig& c = GC::get();
  chat.entries.push_back({NORMAL,
  c.chatMessages.inventoryIsFull});  
}
