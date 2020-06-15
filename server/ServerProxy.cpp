#include "ServerProxy.h"

#include <iostream>
#include <vector>
#include <unistd.h>

ServerProxy::ServerProxy(InstructionDataBQ &instructionQueue, 
  ActivePlayers &activePlayers): instructionQueue(instructionQueue), 
  continuePlaying(true), activePlayers(activePlayers), clientBQ(1){
}

void ServerProxy::run(){
  /* Con este id, genero una nueva instrucción loadPlayer, y la pusheo
  a la instructionQueue para que el jugador sea dado de alta con sus
  respectivos datos de MainPlayerData almacenado en la base de datos. */
  size_t id = activePlayers.authenticate(clientBQ);

  sleep(2*id);
  std::cout << "Hola! Soy el cliento con id " << id << std::endl;

  ParamData z = {"0"};
  InstructionData loadInstruction = {id, LOAD_PLAYER, {z}};
  instructionQueue.push(loadInstruction);
  
  while (continuePlaying){
    ParamData x = {"100"};
    ParamData y = {"200"};
    InstructionData instruction = {id, MOVE, {x,y}};
    instructionQueue.push(instruction);
    stopPlaying();
  }
}

void ServerProxy::stopPlaying(){
  continuePlaying = false;
}

ServerProxy::~ServerProxy(){}
