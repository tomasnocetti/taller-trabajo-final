#include "ServerProxy.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

ServerProxy::ServerProxy(std::string& host, std::string& port) :
  running(true),
  serverProxyWrite(*this, writeBQ),
  serverProxyRead(*this){
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
  serverProxyRead.start();

  ParamData nick = {"Fer"};
  InstructionData instruction = {AUTHENTICATE, {nick}};
  writeBQ.push(instruction);

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

  mainPlayerData.rootd.prace = HUMAN;
  mainPlayerData.position.x = (542 - 11) / 2;
  mainPlayerData.position.y = (413 - 154) / 2;
  mainPlayerData.movement.xDir = 0;
  mainPlayerData.movement.yDir = 0;
  mainPlayerData.points.totalHP = 100;
  mainPlayerData.points.totalMP = 100;
  mainPlayerData.points.currentHP = 100;
  mainPlayerData.points.currentMP = 100;
  mainPlayerData.movement.speed = 2;
  mainPlayerData.gold = 0;
}

void ServerProxy::update() {
  std::unique_ptr<Response> r;

  if (!running) return;
  bool success = responseQ.try_front_pop(r);

  if (!success) return;
  r->run(*this);
}

void ServerProxy::move(int xDir, int yDir){
  /* Código para mockear */
  mainPlayerData.movement.xDir = xDir;
  mainPlayerData.movement.yDir = yDir;
  mainPlayerData.position.x += xDir * mainPlayerData.movement.speed;
  mainPlayerData.position.y += yDir * mainPlayerData.movement.speed;

  if (xDir == 0 && yDir == 0) return;

  ParamData x = {std::to_string(xDir)};
  ParamData y = {std::to_string(yDir)};
  InstructionData instruction = {MOVE, {x, y}};
  writeBQ.push(instruction);
}

// Codigo para MOCKEAR
void ServerProxy::moveNPC(int xDir, int yDir){
  for (unsigned int i = 0; i < npcs.size(); i++){
    npcs[i].movement.xDir = xDir;
    npcs[i].movement.yDir = yDir;
    npcs[i].position.x += xDir * npcs[i].movement.speed;
    npcs[i].position.y += yDir * npcs[i].movement.speed;
  }
}

MainPlayerData ServerProxy::getMainPlayerData() const {
  return mainPlayerData;
}

void ServerProxy::setGameModelData(PlayerGameModelData &gameModelData){
  mainPlayerData = gameModelData.playerData;
  npcs = gameModelData.npcs;
  otherPlayers = gameModelData.otherPlayers;
  map = gameModelData.map;
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
