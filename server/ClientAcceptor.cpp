#include "ClientAcceptor.h"
#include <utility>
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
      std::cerr << "Error en ClientAcceptor: \n" <<
        " Codigo: " << e.code().value() <<
        " Error: " << e.what() << std::endl;
    }
  } catch(const std::exception& e) {
    std::cerr << "Error en ClientAcceptor: \n" <<
      " Error: " << e.what() << std::endl;
  } catch(...) {
    std::cerr << "Error en ClientAcceptor: \n" <<
      " Error Invalido" << std::endl;
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

    i->stop();
    i->join();

    return true;
  });
}

void ClientAcceptor::stop(){
  running = false;
  /** Shutdown is needed for Linux */
  bindedSocket.shutdown();
  /** Close is needed for OSX */
  bindedSocket.close();
  for (auto &i : clientProxies) {
    i->join();
  }
  for (auto &i : clientProxies) {
    i->stop();
  }
  this->join();
}
