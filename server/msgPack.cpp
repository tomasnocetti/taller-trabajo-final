#include "msgPack.h"
#include "iostream"

#define SUCCESS 0

MsgPack::MsgPack(){}

std::stringstream MsgPack::Pack(msgpack::type::tuple<int, int, std::string> src){
  std::stringstream buffer_to_send;
  msgpack::pack(buffer_to_send, src);
  return buffer_to_send;
}

int MsgPack::Unpack(std::stringstream &buffer_recv){
  // deserialize the buffer into msgpack::object instance.
  std::string str(buffer_recv.str());

  msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());

  // deserialized object is valid during the msgpack::object_handle instance is alive.
  msgpack::object deserialized = oh.get();

  print_msg(deserialized);

  return SUCCESS;
}

int MsgPack::print_msg(msgpack::object msg_recv){
  std::cout << msg_recv << std::endl;
  return SUCCESS;
}

MsgPack::~MsgPack(){}

