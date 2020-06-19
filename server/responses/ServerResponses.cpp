#include "Response.h"

#include <string>

PlayerGameResponse::PlayerGameResponse(
  PlayerGameModelData model) :
  Response(ResponseTypeT::PLAYER_GAME_MODEL),
  model(model) {}


std::string PlayerGameResponse::pack() {
  /** LOGICA PARA PACKEAR LA RESPUESTA ACORDE AL PROTOCOLO
   * TIPODERESPUESTA - 4 bytes de largo - contenido
  */
 std::string r("mypackedresponse");
 return r;
}