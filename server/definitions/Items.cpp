#include "Items.h"

Item::Item(int id, Equipable type, std::string name) :
  id(id),
  type(type),
  name(name) {}

BodyItem::BodyItem(
  int id,
  Equipable type,
  std::string name,
  int minDefense,
  int maxDefense) :
  Item(id, type, name),
  minDefense(minDefense),
  maxDefense(maxDefense) {}

HeadItem::HeadItem(
  int id,
  Equipable type,
  std::string name,
  int minDefense,
  int maxDefense) :
  Item(id, type, name),
  minDefense(minDefense),
  maxDefense(maxDefense) {}

LeftHandItem::LeftHandItem(
  int id,
  Equipable type,
  std::string name,
  int minDefense,
  int maxDefense) :
  Item(id, type, name),
  minDefense(minDefense),
  maxDefense(maxDefense) {}

RightHandItem::RightHandItem(
    int id,
    Equipable type,
    std::string name,
    int minDamage,
    int maxDamage,
    int mana,
    int range) :
  Item(id, type, name),
  minDamage(minDamage),
  maxDamage(maxDamage),
  range(range),
  mana(mana) {}

void RightHandItem::equip(Player& p) {
  p.rightSkills.maxDamage = maxDamage;
  p.rightSkills.minDamage = minDamage;
  p.rightSkills.range = range;
  p.rightSkills.mana = mana;
}

void LeftHandItem::equip(Player& p) {
  p.leftSkills.maxDefense = maxDefense;
  p.leftSkills.minDefense = maxDefense;
}

void BodyItem::equip(Player& p) {
  p.bodySkills.maxDefense = maxDefense;
  p.bodySkills.minDefense = minDefense;
}

void HeadItem::equip(Player& p) {
  p.headSkills.maxDefense = maxDefense;
  p.headSkills.minDefense = maxDefense;
}