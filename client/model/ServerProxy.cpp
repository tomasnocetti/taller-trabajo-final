#include "ServerProxy.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

ServerProxy::ServerProxy(std::string& host, std::string& port) :
  running(true),
  authentificated(false),
  creationMode(false),
  serverProxyWrite(*this, writeBQ),
  serverProxyRead(*this){
    socket.connect(host.c_str(), port.c_str());
}

void ServerProxy::init() {
  serverProxyWrite.start();
  serverProxyRead.start();
}

void ServerProxy::authentificate(std::string& alias, std::string& password) {
  if (authentificated) return;
  ParamData nick = {alias};
  ParamData pw = {password};
  InstructionData instruction = {AUTHENTICATE, {nick, pw}};
  writeBQ.push(instruction);
}

void ServerProxy::update() {
  std::unique_ptr<Response> r;

  if (!running) return;
  
  while (true){
    bool success = responseQ.try_front_pop(r);
    if (!success) return;
    r->run(*this);
  }
}

void ServerProxy::move(int xDir, int yDir){
  if (!authentificated) return;
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
  if (!authentificated) return;
  ParamData x = {std::to_string(xPos)};
  ParamData y = {std::to_string(yPos)};
  ParamData width = {std::to_string(mainPlayer.position.w)};
  ParamData height = {std::to_string(mainPlayer.position.h)};
  InstructionData instruction = {ATTACK, {x, y, width, height}};
  writeBQ.push(instruction);
}

void ServerProxy::equip(int inventoryPosition){
  if (!authentificated) return;
  ParamData pos = {std::to_string(inventoryPosition)};
  InstructionData instruction = {EQUIP, {pos}};
  writeBQ.push(instruction);
}

const MainPlayerData& ServerProxy::getMainPlayerData() const {
  return mainPlayer;
}

void ServerProxy::setGameModelData(PlayerGameModelData &gameModelData){
  authentificated = true;
  creationMode = false;
  mainPlayer = gameModelData.playerData;
  npcs = gameModelData.npcs;
  otherPlayers = gameModelData.otherPlayers;
  drops = gameModelData.drops;
  gameSounds = gameModelData.gameSounds;
  for (auto &it : gameSounds){
    std::cout << it.itemId;
  }
}

void ServerProxy::setMapData(MapData& mapData){
  mapSet = true;
  map = mapData;
}

const MapData& ServerProxy::getMapData() const {
  return map;
}

const std::vector<EnemyData>& ServerProxy::getNPCData() const {
  return npcs;
}

const std::vector<OtherPlayersData>& ServerProxy::getOtherPlayersData() const {
  return otherPlayers;
}

const std::vector<DropItemData>& ServerProxy::getDrops() const {
  return drops;
}

/*
const SoundData ServerProxy::getSound() const {
  return gameSound;
}
*/
/*
void ServerProxy::clearSound() {
  gameSound.itemId = 0;
  gameSound.xPos = 0;
  gameSound.yPos = 0;
}
*/
bool ServerProxy::isAuthenticated() const {
  return authentificated;
}

bool ServerProxy::isInCreationMode() const {
  return creationMode;
}

void ServerProxy::setInCreationMode() {
  creationMode = true;
}

bool ServerProxy::isMapSet() const {
  return mapSet;
}

void ServerProxy::close(){
  running = false;
  writeBQ.close();
}

void ServerProxy::resurrect(){
  if (!authentificated) return;
  InstructionData instruction = {RESURRECT, {}};
  writeBQ.push(instruction);
}

void ServerProxy::meditate(){
  if (!authentificated) return;
  InstructionData instruction = {MEDITATE, {}};
  writeBQ.push(instruction);
}

void ServerProxy::throwObject(std::string &inventoryPosition){
  ParamData x = {inventoryPosition};
  InstructionData instruction = {THROW_OBJECT, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::pickUp(){
  InstructionData instruction = {PICK_UP, {}};
  writeBQ.push(instruction);
}

void ServerProxy::list(){
  InstructionData instruction = {LIST, {}};
  writeBQ.push(instruction);
}

void ServerProxy::buy(std::string &itemNumber){
  ParamData x = {itemNumber};
  InstructionData instruction = {BUY, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::sell(std::string &itemNumber){
  ParamData x = {itemNumber};
  InstructionData instruction = {SELL, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::heal(){
  InstructionData instruction = {HEAL, {}};
  writeBQ.push(instruction);
}

void ServerProxy::depositGold(std::string &amount){
  ParamData x = {amount};
  InstructionData instruction = {DEPOSIT_GOLD, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::depositItem(std::string &inventoryPos){
  ParamData x = {inventoryPos};
  InstructionData instruction = {DEPOSIT_ITEM, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::withDrawGold(std::string &amount){
  ParamData x = {amount};
  InstructionData instruction = {WITHDRAW_GOLD, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::withDrawItem(std::string &inventoryPos){
  ParamData x = {inventoryPos};
  InstructionData instruction = {WITHDRAW_ITEM, {x}};
  writeBQ.push(instruction);
}

void ServerProxy::createPlayer(
  std::string &nick, 
  std::string &password, 
  std::string &race,
  std::string &typeClass){
  ParamData n = {nick};
  ParamData p = {password};
  ParamData r = {race};
  ParamData c = {typeClass};
  InstructionData instruction = {CREATE_PLAYER, {n, p, r, c}};
  writeBQ.push(instruction);
}

void ServerProxy::sendMessageToPlayer(std::string &nick, std::string &message){
  ParamData n = {nick};
  ParamData msg = {message};
  InstructionData instruction = {SEND_MESSAGE, {n, msg}};
  writeBQ.push(instruction);
}
