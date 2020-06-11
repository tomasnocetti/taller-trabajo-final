#include "ClientAcceptor.h"
#include <utility>

ClientAcceptor::ClientAcceptor(InstructionDataBQ &updateModel) 
: updateModel(updateModel){}

ClientAcceptor::~ClientAcceptor(){}

void ClientAcceptor::run(){
  /*Esperar nuevas conexiones e ir lanzando serverProxies*/
  int i = 0;
  while (i < 2){
    acceptPlayer();
    i++;
  }
}

void ClientAcceptor::acceptPlayer(){
  std::unique_ptr<ServerProxy> p(new ServerProxy(updateModel));
  p->run();
  serverProxies.push_back(std::move(p));
}
