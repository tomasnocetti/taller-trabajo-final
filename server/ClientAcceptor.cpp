#include "ClientAcceptor.h"
#include <utility>
#include <syslog.h>
#include <iostream>

ClientAcceptor::ClientAcceptor(char* port, InstructionBQ &instructionQueue) :
  instructionQueue(instructionQueue),
  running(true) {
    bindedSocket.bind_and_listen(port);
}

ClientAcceptor::~ClientAcceptor(){}

void ClientAcceptor::run(){
  try{
    /*Esperar nuevas conexiones e ir lanzando ClientProxies*/
    while (running){
      acceptClient();
      cleanCloseClients();
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
    new ClientProxy(instructionQueue, bindedSocket.accept()));
  p->start();
  clientProxies.push_back(std::move(p));
}

void ClientAcceptor::cleanCloseClients(){
  clientProxies.remove_if([](std::unique_ptr<ClientProxy> &i) {
    if (!i->isClose()) return false;
    return true;
  });
}
