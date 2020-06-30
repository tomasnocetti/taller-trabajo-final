#ifndef ITEMS_H
#define ITEMS_H

#include "../../DataDefinitions.h"
#include "../ecs/Player.h"

class Player;

struct Item {
  Item(int id, Equipable type, std::string name);
  int id;
  Equipable type;
  std::string name;
  virtual void equip(Player& player) {};
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
  virtual void equip(Player& player) override;
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
  virtual void equip(Player& player) override;
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
  virtual void equip(Player& player) override;
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
  virtual void equip(Player& player) override;
};

#endif
