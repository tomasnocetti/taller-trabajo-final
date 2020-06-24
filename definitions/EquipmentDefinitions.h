#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

typedef enum {
  DEFAULT,
  HELMET
} HeadEquipment;

MSGPACK_ADD_ENUM(HeadEquipment)

typedef enum {
  DEFAULT,
  TUNIC
} BodyEquipment;

MSGPACK_ADD_ENUM(BodyEquipment)

typedef enum {
  DEFAULT,
  SWORD
} RightHandEquipment;

MSGPACK_ADD_ENUM(RightHandEquipment)

typedef enum {
  DEFAULT,
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
