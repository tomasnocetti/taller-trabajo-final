#include "ClientProxy.h"

#include <iostream>
#include <string>
#include <vector>
#include <iostream>

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
  data.type = SKELETON;
  npcs.emplace_back(data);

  data.position.x = 600;
  data.position.y = 600;
  data.type = GOBLIN;
  npcs.emplace_back(data);

  // ------ TEST CODE FOR ENEMIES
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
