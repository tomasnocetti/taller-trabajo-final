#include "ClientAcceptor.h"
#include <utility>
#include <syslog.h>

ClientAcceptor::ClientAcceptor(InstructionBQ &instructionQueue) :
  instructionQueue(instructionQueue) {}

ClientAcceptor::~ClientAcceptor(){}

void ClientAcceptor::run(){
  try{
    /*Esperar nuevas conexiones e ir lanzando ClientProxies*/
    int i = 0;
    while (i < 2){
      acceptClient();
      i++;
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

void ClientAcceptor::acceptClient(){
  std::unique_ptr<ClientProxy> p(
    new ClientProxy(instructionQueue));

  p->start();
  serverProxies.push_back(std::move(p));
}
