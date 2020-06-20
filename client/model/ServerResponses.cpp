#include "Response.h"

#include <string>
#include <iostream>

PlayerGameResponse::PlayerGameResponse(std::string &buffer) :
  Response(ResponseTypeT::PLAYER_GAME_MODEL) {
  /** LOGICA PARA UNPACKEAR LA RESPUESTA Y SETEAR EL MODELO INTERNO
   * - unpackeo contenido
   * - seteo la propiedad interna del modelo
  */
  msgpack::object_handle oh =
        msgpack::unpack(buffer.data(), buffer.size());
  msgpack::object deserialized = oh.get();
  model = deserialized.as<PlayerGameModelData>();
  std::cout << deserialized << std::endl;
}

void PlayerGameResponse::run(ServerProxy& server) {
  
}
