#ifndef ITEMS_H
#define ITEMS_H

#include "../../DataDefinitions.h"
#include "../ecs/Player.h"
#include <string>

class Player;

struct Item {
  Item(int id, Equipable type, std::string name);
  virtual ~Item() {};
  int id;
  Equipable type;
  std::string name;
  virtual void equip(Player& player) const = 0;
};

struct RightHandItem : Item {
  RightHandItem(
    int id,
    Equipable type,
    std::string name,
    int minDamage,
    int maxDamage,
    int mana,
    int range);
  int minDamage;
  int maxDamage;
  int range;
  int mana;
  void equip(Player& player) const override;
};

struct LeftHandItem : Item {
  LeftHandItem(
    int id,
    Equipable type,
    std::string name,
    int minDefense,
    int maxDefense);
  int minDefense;
  int maxDefense;
  void equip(Player& player) const override;
};

struct BodyItem : Item {
  BodyItem(
    int id,
    Equipable type,
    std::string name,
    int minDefense,
    int maxDefense);
  int minDefense;
  int maxDefense;
  void equip(Player& player) const override;
};

struct HeadItem : Item {
  HeadItem(
    int id,
    Equipable type,
    std::string name,
    int minDefense,
    int maxDefense);
  int minDefense;
  int maxDefense;
  void equip(Player& player) const override;
};

#endif
