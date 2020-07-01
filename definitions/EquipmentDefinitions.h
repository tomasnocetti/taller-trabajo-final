#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

#include <msgpack.hpp>

typedef enum {
  HEALTH_POTION = 'V',
  MANA_POTION = 'M',
  WEAPON = 'W',
  LEFT_HAND_DEFENSE = 'L',
  HEAD_DEFENSE = 'H',
  BODY_ARMOUR = 'B'
} Equipable;

MSGPACK_ADD_ENUM(Equipable)

struct EquipmentData {
  int head;
  int body;
  int rightHand;
  int leftHand;
  MSGPACK_DEFINE(head, body, rightHand, leftHand)
};

struct RightHandEquipmentSkills{
  int maxDamage;
  int minDamage;
  int range;
  int mana;
};

struct LeftHandEquipmentSkills{
  int maxDefense;
  int minDefense;
};

struct BodyEquipmentSkills{
  int maxDefense;
  int minDefense;
};

struct HeadEquipmentSkills{
  int maxDefense;
  int minDefense;
};

#endif
