#include "Response.h"

#include <string>

PlayerGameResponse::PlayerGameResponse(std::string buffer) :
  Response(ResponseTypeT::PLAYER_GAME_MODEL) {
  /** LOGICA PARA UNPACKEAR LA RESPUESTA Y SETEAR EL MODELO INTERNO
   * - unpackeo contenido
   * - seteo la propiedad interna del modelo
  */
}

void PlayerGameResponse::run(ServerProxy& server) {

}