#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

#include <msgpack.hpp>

typedef enum {
  HEALTH_POTION = 'HP',
  MANA_POTION = 'MP',
  WEAPON = 'W',
  LEFT_HAND_DEFENSE = 'L',
  HEAD_DEFENSE = 'H',
  BODY_ARMOUR = 'B'
} Equipable;

MSGPACK_ADD_ENUM(Equipable)

typedef enum{
  DEFAULT_H,
  HELMET,
  HAT,
  HOOD
} HeadEquipment;

MSGPACK_ADD_ENUM(HeadEquipment)

typedef enum {
  DEFAULT_B,
  TUNIC,
  LEATHER_ARMOR,
  PLATE_ARMOR
} BodyEquipment;

MSGPACK_ADD_ENUM(BodyEquipment)

typedef enum {
  DEFAULT_R,
  SWORD,
  SIMPLE_BOW,
  ASH_STICK,
  GNARLED_STAFF
} RightHandEquipment;

MSGPACK_ADD_ENUM(RightHandEquipment)

typedef enum {
  DEFAULT_L,
  TURTLE_SHIELD,
  IRON_SHIELD
} LeftHandEquipment;

MSGPACK_ADD_ENUM(LeftHandEquipment)

typedef enum {
  HEALTH,
  MANA
} Potions;

MSGPACK_ADD_ENUM(Potions)

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
