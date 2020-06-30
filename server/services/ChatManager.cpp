#include "ChatManager.h"

void ChatManager::initialMessage(ChatData &chat){
  chat.entries.push_back({INFO, INITIAL_MSG});
}

void ChatManager::damageReceived(ChatData &chat, int damage){
  chat.entries.push_back({DANGER, 
      DAMAGE_RCV_MSG + std::to_string(damage)});
}

void ChatManager::enemyDodgedTheAttack(ChatData &chat){
  chat.entries.push_back({INFO, ENEMY_DODGED_ATTACK});
}

void ChatManager::attackDodged(ChatData &chat){
  chat.entries.push_back({SUCCESS, ATTACK_DODGED});
}

void ChatManager::damageCaused(ChatData &chat, int damage){
  chat.entries.push_back({SUCCESS, DAMAGE_CAUSED + std::to_string(damage)});
}

/*
  mainPlayer.chat.entries.push_back({INFO, "Bienvenido Tomas"});
  mainPlayer.chat.entries.push_back({DANGER, "Te atacaron por 100 puntos"});
  mainPlayer.chat.entries.push_back({SUCCESS, "Atacaste por 100 puntos"});
  mainPlayer.chat.entries.push_back({NORMAL, "Lista de items a comprar:"});

*/
