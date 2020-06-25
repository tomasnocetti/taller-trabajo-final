#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

#include <msgpack.hpp>

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
  SWORD
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
};

struct LeftHandEquipmentSkills{
  int maxDamage;
  int minDamage;
};

struct BodyEquipmentSkills{
  int maxDamage;
  int minDamage;
};

struct HeadEquipmentSkills{
  int maxDamage;
  int minDamage;
};

#endif
