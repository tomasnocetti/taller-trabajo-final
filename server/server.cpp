#include <iostream>
#include <sstream>
#include <cassert>
#include "../DataDefinitions.h"
#include "GameServer.h" 

int main() {
  GameServer game;
  game.start();
  
  return 0;
}

/*
  ParamData_t param = {"300"};
  InstructionData data = {100, {param}};

  // packing
  std::stringstream ss;
  msgpack::pack(ss, data);

  // unpacking
  msgpack::object_handle oh = msgpack::unpack(ss.str().data(), ss.str().size());
  msgpack::object const& obj = oh.get();
  std::cout << "object: " << obj << std::endl;
  
  InstructionData data_out = obj.as<InstructionData>();
  std::cout << data_out.playerId << std::endl;
  std::cout << data_out.params.at(0).value << std::endl;
  */
