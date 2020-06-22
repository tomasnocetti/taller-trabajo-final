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
  mainPlayer.rootd.pclass = WARRIOR;
  mainPlayer.rootd.prace = HUMAN;
  mainPlayer.position.x = 100;
  mainPlayer.position.y = 100;
/*
  mainPlayer.movement.isMoving = false;
  mainPlayer.level = 0;
  mainPlayer.points.totalHP = 100;
  mainPlayer.points.totalMP = 100;
  mainPlayer.points.currentHP = 100;
  mainPlayer.points.currentMP = 100;
  mainPlayer.movement.speed = 2;
  mainPlayer.gold = 0;
*/
}

void ServerProxy::update() {
  std::unique_ptr<Response> r;

  if (!running) return;
  bool success = responseQ.try_front_pop(r);

  if (!success) return;
  r->run(*this);
}

void ServerProxy::move(int xDir, int yDir){
  if (xDir == 0 && yDir == 0){
    InstructionData instruction = {STOP_MOVEMENT, {}};
    writeBQ.push(instruction);
  } else {
    ParamData x = {std::to_string(xDir)};
    ParamData y = {std::to_string(yDir)};
    InstructionData instruction = {MOVE, {x, y}};
    writeBQ.push(instruction);
  }
}

void ServerProxy::attack(int xPos, int yPos) {
  std::cout << xPos << std::endl;
  std::cout << yPos << std::endl;
  std::cout << std::endl;
}

MainPlayerData ServerProxy::getMainPlayerData() const {
  return mainPlayer;
}

void ServerProxy::setGameModelData(PlayerGameModelData &gameModelData){
  mainPlayer = gameModelData.playerData;
  npcs = gameModelData.npcs;
  otherPlayers = gameModelData.otherPlayers;
  map = gameModelData.map;
  std::cout << "Jugador movido a: x:" << mainPlayer.position.y <<
    " y: " << mainPlayer.position.x << std::endl;
}

MapData ServerProxy::getMapData() const {
  return map;
}

std::vector<EnemyData> ServerProxy::getNPCData() const {
  return npcs;
}

std::vector<OtherPlayersData> ServerProxy::getOtherPlayersData() const {
  return otherPlayers;
}

bool ServerProxy::isAuthenticated() const {
  return authentificated;
}

void ServerProxy::close(){
  running = false;
  InstructionData instruction = {CLOSE_SERVER, {}};
  writeBQ.push(instruction);
}
