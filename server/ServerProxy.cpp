#include "ServerProxy.h"

#include <iostream>
#include <vector>

ServerProxy::ServerProxy(InstructionDataBQ &updateModel): 
  updateModel(updateModel), continuePlaying(true){
    player.create();
}

void ServerProxy::run(){
  while (continuePlaying){
    ParamData x = {"100"};
    ParamData y = {"200"};
    InstructionData instruction = {0001, MOVE, {x,y}};
    updateModel.push(instruction);
    stopPlaying();
  }
}

void ServerProxy::stopPlaying(){
  continuePlaying = false;
}

void ServerProxy::movePlayer(uint32_t direction){
  std::vector<int> coordinates = player.estimateCoordintates(direction);
}

ServerProxy::~ServerProxy(){}
