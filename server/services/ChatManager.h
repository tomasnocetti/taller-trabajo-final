#ifndef CHAT_MANAGER_H
#define CHAT_MANAGER_H

#include "../../definitions/ChatDefinitions.h"

class ChatManager{
  public:
    ChatManager();
    ~ChatManager();
    ChatManager(const ChatManager&) = delete;
    ChatManager& operator=(const ChatManager&) = delete;
    static void initialMessage(ChatData &chat);
    static void damageReceived(ChatData &chat, int damage);
    static void enemyDodgedTheAttack(ChatData &chat);
    static void attackDodged(ChatData &chat);
    static void damageCaused(ChatData &data, int damage);

  private:
};

#endif
