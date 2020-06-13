#include "ActivePlayers.h"
#include <iostream>
#include <utility>
#include <vector>

ActivePlayers::ActivePlayers(size_t id) : id(id){}

ActivePlayers::~ActivePlayers(){}

size_t ActivePlayers::authenticate(UpDateClientsBQ &clientBQ){
  std::unique_lock<std::mutex> lk(this->m);
  models.insert(std::pair<size_t, UpDateClientsBQ&>(id, clientBQ));
  id ++;
  return id - 1;
}

void ActivePlayers::deAuthenticate(size_t id){
  std::unique_lock<std::mutex> lk(this->m);
  models.erase(id);
}

std::vector<size_t> ActivePlayers::getActivePlayers(){
  std::unique_lock<std::mutex> lk(this->m);
  std::vector<size_t> playersId;
  for (auto const& element : models) {
    playersId.push_back(element.first);
  }
  return playersId;
}

void ActivePlayers::updateModel(){}
