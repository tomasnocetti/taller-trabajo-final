#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

#include <msgpack.hpp>

typedef enum{
  DEFAULT1,
  HELMET,
  HAT
} HeadEquipment;

MSGPACK_ADD_ENUM(HeadEquipment)

typedef enum {
  DEFAULT2,
  TUNIC
} BodyEquipment;

MSGPACK_ADD_ENUM(BodyEquipment)

typedef enum {
  DEFAULT3,
  SWORD
} RightHandEquipment;

MSGPACK_ADD_ENUM(RightHandEquipment)

typedef enum {
  DEFAULT4,
  SHIELD
} LeftHandEquipment;

MSGPACK_ADD_ENUM(LeftHandEquipment)

struct EquipmentData {
  HeadEquipment head;
  BodyEquipment body;
  RightHandEquipment rightHand;
  LeftHandEquipment leftHand;
  MSGPACK_DEFINE(head, body, rightHand, leftHand)
};

#endif
