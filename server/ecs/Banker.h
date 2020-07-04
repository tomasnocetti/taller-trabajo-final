#ifndef BANKER_H
#define BANKER_H

#include "Entity.h"
#include "Player.h"
#include <vector>
#include <string>
#include "../../DataDefinitions.h"
#include "../GameModel.h"

class Player;

class Banker : public Entity {
  public:
    explicit Banker(PositionData position);
    Banker(const Banker&) = delete;
    Banker& operator=(const Banker&) = delete;
    static size_t getNewId();
    void listItems(Player &player);
    void deposit(Player &player, size_t inventoryPos);
    void withdraw(Player &player, size_t inventoryPos);
    void depositGold(Player &player, size_t amount);
    void withDrawGold(Player &player, size_t amount);

  private:
    static size_t idGenerator;
    friend class GameModel;
};

#endif
