#ifndef PRIEST_H
#define PRIEST_H

#include "Entity.h"
#include "Player.h"
#include <vector>
#include <string>
#include "../../DataDefinitions.h"
#include "../GameModel.h"

class Player;

class Priest : public Entity {
  public:
    explicit Priest(PositionData position);
    Priest(const Priest&) = delete;
    Priest& operator=(const Priest&) = delete;
    void sell(size_t option, Player &player);
    std::vector<std::string>& getItemsList();
    static size_t getNewId();
    void listItems(Player &player);

  private:
    std::vector<std::string> readableItems;
    static size_t idGenerator;
    friend class GameModel;
};

#endif
