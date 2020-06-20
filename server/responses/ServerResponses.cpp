#include "Response.h"
#include "../../common/common_utils.h"

#include <string>
#include <sstream>

PlayerGameResponse::PlayerGameResponse(
  PlayerGameModelData model) :
  Response(ResponseTypeT::PLAYER_GAME_MODEL) {
    /** LOGICA PARA PACKEAR LA RESPUESTA ACORDE AL PROTOCOLO
     * TIPODERESPUESTA - 4 bytes de largo - contenido
    */

    std::stringstream buffer;
    msgpack::pack(buffer, model);
    
    std::string str(buffer.str());

    size_t length = to_big_end<uint32_t>(str.length());
    str.insert(0, (char *) &length, 4);

    size_t responseType = type;
    str.insert(0, (char *) &responseType, 1);

    modelPacked = str;
}

std::string PlayerGameResponse::getModelPacked(){
  return modelPacked;
}
