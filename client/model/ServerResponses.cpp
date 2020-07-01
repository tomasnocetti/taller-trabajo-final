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
}

void PlayerGameResponse::run(ServerProxy& server) {
  server.setGameModelData(model);
}

MapResponse::MapResponse(std::string &buffer) :
  Response(ResponseTypeT::MAP_MODEL) {
  /** LOGICA PARA UNPACKEAR LA RESPUESTA Y SETEAR EL MODELO INTERNO
   * - unpackeo contenido
   * - seteo la propiedad interna del modelo
  */
  msgpack::object_handle oh =
        msgpack::unpack(buffer.data(), buffer.size());
  msgpack::object deserialized = oh.get();
  model = deserialized.as<MapData>();
}

void MapResponse::run(ServerProxy& server) {
  server.setMapData(model);
}

