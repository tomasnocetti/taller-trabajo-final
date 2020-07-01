#ifndef TRADER_H
#define TRADER_H

#include "Entity.h"
#include "Player.h"
#include <vector>
#include <string>
#include "../../DataDefinitions.h"
#include "../GameModel.h"

class Player;

class Trader : public Entity {
  public:
    explicit Trader(PositionData position);
    Trader(const Trader&) = delete;
    Trader& operator=(const Trader&) = delete;
    void buy(Player& p, size_t option);
    void sell(size_t option);
    std::vector<std::string>& getItemsList();

  private:
    std::vector<std::string> readableItems;
    static size_t idGenerator;
    friend class GameModel;
};

#endif
