#ifndef __EQUIPDEF_H
#define __EQUIPDEF_H

typedef enum {
  DEFAULT,
  HELMET
} HeadEquipment;

typedef enum {
  DEFAULT,
  TUNIC
} BodyEquipment;

typedef enum {
  DEFAULT,
  SWORD
} RightHandEquipment;

typedef enum {
  DEFAULT,
  SHIELD
} LeftHandEquipment;

struct EquipmentData {
  HeadEquipment head;
  BodyEquipment body;
  RightHandEquipment righHand;
  LeftHandEquipment leftHand;
};

#endif
