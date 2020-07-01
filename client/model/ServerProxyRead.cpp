#include "ServerProxy.h"
#include <iostream>
#include <syslog.h>
#include <string>
#include <vector>
#include "../../common/common_utils.h"

ServerProxyRead::ServerProxyRead(ServerProxy& server) :
  server(server) {}

void ServerProxyRead::run(){
  try{
    while (server.running){
      handleResponse();
    }
  } catch(const std::system_error& e) {
    /** This error codes gey by-passed. If user closes the game then the connection
     * will be closed by other thread. In this situation the read will throw a EBADF error
     * code, so if the server is off and we get this error we skip.
    */
    if (server.running == false && e.code().value() == EBADF) return;

    syslog(
      LOG_CRIT,
      "[Crit] Error!: \n Error Code: %i \n Message: %s",
      e.code().value(), e.what());
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
  }
}

void ServerProxyRead::handleResponse() {
  ResponseTypeT rtype = ResponseTypeT::DEFAULT;
  server.socket.receive((char*) &rtype, 1);

  uint32_t sizeOfResponse = 0;
  server.socket.receive((char*) &sizeOfResponse, 4);
  sizeOfResponse = from_big_end<uint32_t>(sizeOfResponse);

  std::vector<char> res_message(sizeOfResponse);

  server.socket.receive(res_message.data(), sizeOfResponse);
  std::string response(res_message.begin(), res_message.end());

  std::unique_ptr<Response> r;

  switch (rtype) {
    case ResponseTypeT::PLAYER_GAME_MODEL:
      r = std::unique_ptr<PlayerGameResponse>(
        new PlayerGameResponse(response));
      server.responseQ.push(std::move(r));
      break;
    case ResponseTypeT::MAP_MODEL:
      r = std::unique_ptr<MapResponse>(
        new MapResponse(response));
      server.responseQ.push(std::move(r));
      break;
    default:
      break;
  }
}
