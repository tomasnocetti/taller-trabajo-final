#include "ClientProxy.h"
#include <iostream>
#include <string>
#include <vector>

ClientProxy::ClientProxy(std::string& host, std::string& port) {
  std::cout << "Connected to: " << host << ":" << port << std::endl;
}

void ClientProxy::authentificate(std::string& alias) {
  std::cout << "Player " << alias << " authentificated" << std::endl;
}

void ClientProxy::init() {
  MapParser m;
  m.loadMap("client/assets/map/pindonga2.json");
  map = m.getMapData();

  // ------ TEST CODE FOR PARSE OBJ LAYER
  std::vector<struct ObjectLayerData>& objectl = m.getObjectLayers();

  for (size_t i = 0; i < objectl.size(); i++){
    for (size_t j = 0; j < objectl[i].objects.size(); j++){
      std::cout << objectl[i].objects[j].x << std::endl;
      std::cout << objectl[i].objects[j].y << std::endl;
      std::cout << objectl[i].objects[j].width << std::endl;
      std::cout << objectl[i].objects[j].height << std::endl;
    }
  }

  struct EnemyData data;
  data.position.x = 100;
  data.position.y = 100;
  data.type = GOBLIN;
  npcs.emplace_back(data);

  data.position.x = 200;
  data.position.y = 100;
  data.type = SKELETON;
  npcs.emplace_back(data);

  data.position.x = 300;
  data.position.y = 100;
  data.type = SPIDER;
  npcs.emplace_back(data);
  // ------ TEST CODE FOR ENEMIES

  mainPlayer.position.x = (542 - 11) / 2;
  mainPlayer.position.y = (413 - 154) / 2;
  mainPlayer.points.totalHP = 100;
  mainPlayer.points.totalMP = 100;
  mainPlayer.points.currentHP = 100;
  mainPlayer.points.currentMP = 100;
  mainPlayer.speed = 2;
  mainPlayer.gold = 0;
}

void ClientProxy::walk(int x, int y){
  mainPlayer.position.x += x * mainPlayer.speed;
  mainPlayer.position.y += y * mainPlayer.speed;
}

void ClientProxy::walkNPC(int x, int y){
  for(unsigned int i = 0; i < npcs.size(); i++){
    npcs[i].position.x += x;
    npcs[i].position.y += y;
  }
}

MainPlayerData ClientProxy::getMainPlayerData() const {
  return mainPlayer;
}

MapData ClientProxy::getMapData() const {
  return map;
}

std::vector<EnemyData> ClientProxy::getNPCData() const {
  return npcs;
}

bool ClientProxy::isAuthenticated() const {
  return authentificated;
}
