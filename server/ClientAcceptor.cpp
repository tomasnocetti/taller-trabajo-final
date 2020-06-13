#include "ClientAcceptor.h"
#include <utility>

ClientAcceptor::ClientAcceptor(InstructionDataBQ &instructionQueue, 
  ActivePlayers &activePlayers) : instructionQueue(instructionQueue),
  activePlayers(activePlayers){}

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
  std::unique_ptr<ServerProxy> p(new ServerProxy(instructionQueue, activePlayers));
  p->start();
  serverProxies.push_back(std::move(p));
}
