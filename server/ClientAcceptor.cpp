#include "ClientAcceptor.h"
#include <utility>

ClientAcceptor::ClientAcceptor(InstructionDataBQ &instructionQueue) :
  instructionQueue(instructionQueue) {}

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
  std::unique_ptr<ClientProxy> p(
    new ClientProxy(instructionQueue));
  p->start();
  serverProxies.push_back(std::move(p));
}
