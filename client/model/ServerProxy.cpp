#include "ServerProxy.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

ServerProxy::ServerProxy(std::string& host, std::string& port) :
  running(true),
  serverProxyWrite(*this, writeBQ),
  serverProxyRead(readBQ){
    std::cout << "Connected to: " << host << ":" << port << std::endl;
    socket.connect(host.c_str(), port.c_str());
}

ServerProxy::~ServerProxy(){
  socket.close();
}

void ServerProxy::authentificate(std::string& alias) {
  std::cout << "Player " << alias << " authentificated" << std::endl;
}

void ServerProxy::init() {
  MapParser m;
  m.loadMap("client/assets/map/pindonga3.json");
  map = m.getMapData();

  serverProxyWrite.start();
  //serverProxyRead.start();

  // ------ TEST CODE FOR PARSE OBJ LAYER
  std::vector<struct ObjectLayerData>& objectl = m.getObjectLayers();

  for (size_t i = 0; i < objectl.size(); i++){
    std::cout << "layer: " << i + 1 << std::endl;
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
  data.movement.speed = 1;
  npcs.emplace_back(data);

  data.position.x = 200;
  data.position.y = 100;
  data.type = SKELETON;
  data.movement.speed = 2;
  npcs.emplace_back(data);

  data.position.x = 300;
  data.position.y = 100;
  data.type = SPIDER;
  data.movement.speed = 3;
  npcs.emplace_back(data);
  // ------ TEST CODE FOR ENEMIES

  mainPlayer.rootd.prace = HUMAN;
  mainPlayer.position.x = (542 - 11) / 2;
  mainPlayer.position.y = (413 - 154) / 2;
  mainPlayer.movement.xDir = 0;
  mainPlayer.movement.yDir = 0;
  mainPlayer.points.totalHP = 100;
  mainPlayer.points.totalMP = 100;
  mainPlayer.points.currentHP = 100;
  mainPlayer.points.currentMP = 100;
  mainPlayer.movement.speed = 2;
  mainPlayer.gold = 0;
}

void ServerProxy::move(int xDir, int yDir){
  /* Código para mockear */
  mainPlayer.movement.xDir = xDir;
  mainPlayer.movement.yDir = yDir;
  mainPlayer.position.x += xDir * mainPlayer.movement.speed;
  mainPlayer.position.y += yDir * mainPlayer.movement.speed;

  if (xDir == 0 && yDir == 0) return;

  ParamData x = {std::to_string(xDir)};
  ParamData y = {std::to_string(yDir)};
  InstructionData instruction = {MOVE, {x, y}};
  writeBQ.push(instruction);
}

void ServerProxy::moveNPC(int xDir, int yDir){
  for (unsigned int i = 0; i < npcs.size(); i++){
    npcs[i].movement.xDir = xDir;
    npcs[i].movement.yDir = yDir;
    npcs[i].position.x += xDir * npcs[i].movement.speed;
    npcs[i].position.y += yDir * npcs[i].movement.speed;
  }
}

MainPlayerData ServerProxy::getMainPlayerData() const {
  return mainPlayer;
}

MapData ServerProxy::getMapData() const {
  return map;
}

std::vector<EnemyData> ServerProxy::getNPCData() const {
  return npcs;
}

bool ServerProxy::isAuthenticated() const {
  return authentificated;
}

void ServerProxy::close(){
  running = false;
  InstructionData instruction = {CLOSE_SERVER, {}};
  writeBQ.push(instruction);
}
