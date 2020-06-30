#ifndef __CHATDEF_H
#define __CHATDEF_H

#include <string>
#include <vector>

#include <msgpack.hpp>

#define CHAT_BASE_X 11
#define CHAT_BASE_Y 15
#define CHAT_BASE_W 541
#define CHAT_BASE_H 180
#define CHAT_CONTENT_X 5
#define CHAT_CONTENT_Y 0
#define CHAT_CONTENT_W 541
#define CHAT_CONTENT_H 108
#define CHAT_BUTTON_X 57
#define CHAT_BUTTON_Y 129
#define CHAT_BUTTON_W 58
#define CHAT_BUTTON_H 15
#define CHAT_INPUT_X 5
#define CHAT_INPUT_Y 116
#define CHAT_INPUT_W 541
#define CHAT_INPUT_H 14
#define CHAT_PADDING_V 4
#define CHAT_LINE_HEIGHT 14

#define INITIAL_MSG "Bienvenido a las tierras de ARGENTUM"
#define DAMAGE_RCV_MSG "Nos estan atacando! Daño recibido: "
#define ENEMY_DODGED_ATTACK "El enemigo ha esquivado el ataque!"
#define ATTACK_DODGED "Ataque esquivado!"
#define DAMAGE_CAUSED "Ataque exitoso! Daño provocado: "

typedef enum{
  INFO,
  DANGER,
  SUCCESS,
  NORMAL
} MessageType;

MSGPACK_ADD_ENUM(MessageType)

struct Entry {
  MessageType type;
  std::string value;
  MSGPACK_DEFINE(type, value)
};

struct ChatData {
  std::vector<Entry> entries;
  MSGPACK_DEFINE(entries)
};

#endif
