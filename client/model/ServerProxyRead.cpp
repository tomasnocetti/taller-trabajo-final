#include "ServerProxy.h"
#include <iostream>
#include <syslog.h>

ServerProxyRead::ServerProxyRead(ServerProxy& server) :
  server(server) {}

void ServerProxyRead::run(){
  try{
    while (server.running){
      handleResponse();
    }
  } catch(const std::system_error& e) {
    /** This error codes gey by-passed. In Linux when a blocking socket.accept
     * is being called and the bind socket get's closed an errno is thrown with
     * EINVAL. This is common logic so it shouldn't be handled as an error.
    */
    if (e.code().value() != ECONNABORTED && e.code().value() != EINVAL) {
      syslog(
        LOG_CRIT,
        "[Crit] Error!: \n Error Code: %i \n Message: %s",
        e.code().value(), e.what());
    }
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
  }
}

void ServerProxyRead::handleResponse() {
  std::unique_ptr<Response> r;
  ResponseTypeT rtype = ResponseTypeT::PLAYER_GAME_MODEL;
  std::string buffer = "ACA VA LA ESTRUCTURA DEL GAME MODEL";

  switch (rtype) {
    case ResponseTypeT::PLAYER_GAME_MODEL:
      r = std::unique_ptr<PlayerGameResponse>(
        new PlayerGameResponse(buffer));
      server.responseQ.push(std::move(r));
      break;
    default:
      break;
  }

};

