#include "ServerProxy.h"

#include <iostream>
#include <vector>
#include <unistd.h>

ServerProxy::ServerProxy(InstructionDataBQ &instructionQueue, 
  ActivePlayers &activePlayers): instructionQueue(instructionQueue), 
  continuePlaying(true), activePlayers(activePlayers), clientBQ(1){
}

void ServerProxy::run(){
  size_t id = activePlayers.authenticate(clientBQ);
  sleep(2*id);
  std::cout << "Hola! Soy el cliento con id " << id << std::endl;
  while (continuePlaying){
    ParamData x = {"100"};
    ParamData y = {"200"};
    InstructionData instruction = {0001, MOVE, {x,y}};
    instructionQueue.push(instruction);
    stopPlaying();
  }
}

void ServerProxy::stopPlaying(){
  continuePlaying = false;
}

ServerProxy::~ServerProxy(){}
