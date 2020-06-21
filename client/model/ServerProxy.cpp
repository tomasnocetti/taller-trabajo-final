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

  mainPlayer.level = 0;
  mainPlayer.rootd.pclass = MAGE;
  mainPlayer.rootd.prace = GNOME;
  mainPlayer.position.x = (542 - 11) / 2;
  mainPlayer.position.y = (413 - 154) / 2;
  mainPlayer.movement.xDir = 0;
  mainPlayer.movement.yDir = 1;
  mainPlayer.movement.isMoving = false;
  mainPlayer.points.totalHP = 100;
  mainPlayer.points.totalMP = 100;
  mainPlayer.points.currentHP = 100;
  mainPlayer.points.currentMP = 100;
  mainPlayer.movement.speed = 5;
  mainPlayer.gold = 0;

  // ------ TEST CODE FOR ENEMIES
  struct EnemyData data;
  data.position.x = 100;
  data.position.y = 100;
  data.movement.xDir = 0;
  data.movement.yDir = 1;
  data.movement.isMoving = false;
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

  OtherPlayersData other;
  other.position.x = 400;
  other.position.y = 100;
  other.rootd.prace = HUMAN;
  other.movement.xDir = 0;
  other.movement.yDir = 1;
  other.movement.isMoving = false;
  other.movement.speed = 1;
  otherPlayers.emplace_back(other);
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
    mainPlayer.movement.isMoving = false;
    InstructionData instruction = {STOP_MOVEMENT, {}};
    writeBQ.push(instruction);
  } else {
    mainPlayer.movement.isMoving = true;
    mainPlayer.movement.xDir = xDir;
    mainPlayer.movement.yDir = yDir;
    mainPlayer.position.x += xDir * mainPlayer.movement.speed;
    mainPlayer.position.y += yDir * mainPlayer.movement.speed;
    ParamData x = {std::to_string(xDir)};
    ParamData y = {std::to_string(yDir)};
    InstructionData instruction = {MOVE, {x, y}};
    writeBQ.push(instruction);
  }
}

void ServerProxy::moveNPC(int index, int xDir, int yDir){
  // for(unsigned int i = 0; i < npcs.size(); i++){
  //   if(xDir == 0 && yDir == 0){
  //     npcs[i].movement.isMoving = false;
  //   } else {
  //     npcs[i].movement.isMoving = true;
  //     npcs[i].movement.xDir = xDir;
  //     npcs[i].movement.yDir = yDir;
  //     npcs[i].position.x += xDir * npcs[i].movement.speed;
  //     npcs[i].position.y += yDir * npcs[i].movement.speed;
  //   }
  // }

  npcs[index].movement.isMoving = true;
  npcs[index].movement.xDir = xDir;
  npcs[index].movement.yDir = yDir;
  npcs[index].position.x += xDir * npcs[index].movement.speed;
  npcs[index].position.y += yDir * npcs[index].movement.speed;
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
  std::cout << "Jugador movido a: x:" << gameModelData.playerData.position.x <<
    " y: " << gameModelData.playerData.position.y << std::endl;
  mainPlayer = gameModelData.playerData;
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

//para agregar otro jugador despues del inicio
void ServerProxy::add(){
  OtherPlayersData other;
  other.position.x = 200;
  other.position.y = 300;
  other.rootd.prace = ELF;
  other.movement.xDir = -1;
  other.movement.yDir = 0;
  other.movement.isMoving = false;
  other.movement.speed = 2;
  otherPlayers.emplace_back(other);
}
