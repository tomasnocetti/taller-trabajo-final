#ifndef MSG_PACK_H
#define MSG_PACK_H

#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <sstream>

class MsgPack {
private:
public:
  MsgPack();
  /* Devuelve un stringstream listo para enviar a través del socket */
  std::stringstream Pack(msgpack::type::tuple<int, int, std::string> src);
  /* Desserializa e imprime por pantalle el buffer */
  int Unpack(std::stringstream &buffer_recv);
  int print_msg(msgpack::object msg_recv);
  ~MsgPack();
};

#endif
