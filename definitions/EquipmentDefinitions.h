#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

#include <msgpack.hpp>

typedef enum {
  POTION,
  WEAPON,
  LEFT_HAND_DEFENSE,
  HEAD_DEFENSE,
  BODY_ARMOUR
} Equipable;

MSGPACK_ADD_ENUM(Equipable)

typedef enum{
  DEFAULT1,
  HELMET,
  HAT,
  HOOD
} HeadEquipment;

MSGPACK_ADD_ENUM(HeadEquipment)

typedef enum {
  DEFAULT2,
  TUNIC,
  LEATHER_ARMOR,
  PLATE_ARMOR
} BodyEquipment;

MSGPACK_ADD_ENUM(BodyEquipment)

typedef enum {
  DEFAULT3,
  SWORD,
  SIMPLE_BOW,
  ASH_STICK
} RightHandEquipment;

MSGPACK_ADD_ENUM(RightHandEquipment)

typedef enum {
  DEFAULT4,
  TURTLE_SHIELD,
  IRON_SHIELD
} LeftHandEquipment;

MSGPACK_ADD_ENUM(LeftHandEquipment)

struct EquipmentData {
  HeadEquipment head;
  BodyEquipment body;
  RightHandEquipment rightHand;
  LeftHandEquipment leftHand;
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

/* Right Hand Skills */

#define SWORD_MIN_DAMAGE 2
#define SWORD_MAX_DAMAGE 5
#define SWORD_RANGE 100

#define SIMPLE_BOW_MIN_DAMAGE 1
#define SIMPLE_BOW_MAX_DAMAGE 4
#define SIMPLE_BOW_RANGE 300

#define ASH_STICK_MIN_DAMAGE 2
#define ASH_STICK_MAX_NDAMAGE 4
#define ASH_STICK_MANA 5
#define ASH_STICK_RANGE 300


/* Body Equipment Skills */

#define TUNIC_MIN_DEFENSE 6
#define TUNIC_MAX_DEFENSE 10

/* Left hand skills */

#define IRON_SHIELD_MIN_DEFENSE 1
#define IRON_SHIELD_MAX_DEFENSE 4

/* Head Skills */
#define HELMET_MIN_DEFENSE 4
#define HELMET_MAX_DEFENSE 8

#endif
