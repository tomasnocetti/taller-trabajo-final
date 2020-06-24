#include "GameModel.h"

#include <iostream>
#include <string> // TODO - Lo pide el parser
#include <utility>
#include <vector>
#include <random>
#include <stdlib.h>

/* Para mockear el id random */
unsigned int seed;

GameModel::GameModel(char* mapPath, CronBQ& cronBQ) :
  cronBQ(cronBQ) {
  m.loadMap(mapPath);
  parseMapData();
}

void GameModel::parseMapData() {
  std::vector<struct ObjectLayerData>& obj = m.getObjectLayers();

  for (size_t i = 0; i < obj.size(); i++){
    ObjectLayerData& layer = obj[i];
    for (size_t j = 0; j < obj[i].objects.size(); j++){
      ObjectData& data = layer.objects[j];
      PositionData p({data.x, data.y, data.width, data.height});

      if (layer.name == MARGIN_LAYER){
        std::unique_ptr<Entity> margin(
          new Entity(p));
        margins.push_back(std::move(margin));
      }
    }
  }
}

GameModel::~GameModel(){}

bool GameModel::authenticate(
  std::string& nick,
  ResponseBQ& responseBQ,
  size_t& playerId) {
  // TODO: BUSCAR EN LOS ARCHIVOS. VER SI EXISTE Y OBTENER DATA//
  if (nick == "Fer") playerId  = rand_r(&seed) % 100;

  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//
  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(playerId, responseBQ));

  PlayerRootData root = {WARRIOR, HUMAN};

  std::unique_ptr<Player> player(Player::createPlayer(playerId, nick, root));
  players.insert(std::pair<size_t,
    std::unique_ptr<Player>>(playerId, std::move(player)));

  return true;
}

void GameModel::move(size_t playerId, int x, int y) {
  players.at(playerId)->movement.xDir = x;
  players.at(playerId)->movement.yDir = y;
}

void GameModel::stopMovement(size_t playerId){
  players.at(playerId)->movement.xDir = 0;
  players.at(playerId)->movement.yDir = 0;
}

void GameModel::attack(size_t playerId, int xPos, int yPos){
  for (auto& it : players){
    if (players.at(it.first)->id == playerId) continue;

    if (!players.at(playerId)->checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    players.at(playerId)->attack(*it.second, xPos, yPos);
  }

  for (auto& it : npcMap){
    if (!players.at(playerId)->checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    players.at(playerId)->attack(*it.second, xPos, yPos);
  }
}

void GameModel::playerSetCoords(size_t playerId, int x, int y) {
  int auxXPos = players.at(playerId)->position.x;
  int auxYPos = players.at(playerId)->position.y;
  players.at(playerId)->position.x = x;
  players.at(playerId)->position.y = y;

  for (auto& it : players){
    if (players.at(it.first)->id == playerId) continue;
    bool collision = players.at(playerId)->checkCollision(*it.second);
    if (collision){
        players.at(playerId)->position.x = auxXPos;
        players.at(playerId)->position.y = auxYPos;
        return;
    }
  }

  for (auto &it : margins){
    bool collision = players.at(playerId)->checkCollision(*it);
    if (collision){
      players.at(playerId)->position.x = auxXPos;
      players.at(playerId)->position.y = auxYPos;
      return;
    }
  }

  for (auto& it : npcMap){
    bool collision = players.at(playerId)->checkCollision(*it.second);
    if (collision){
        players.at(playerId)->position.x = auxXPos;
        players.at(playerId)->position.y = auxYPos;
        return;
    }
  }
}

void GameModel::npcSetCoords(size_t id, int xPos, int yPos){  
    int auxXPos = npcMap.at(id)->position.x;
    int auxYPos = npcMap.at(id)->position.y;
    
    npcMap.at(id)->position.x = xPos;
    npcMap.at(id)->position.y = yPos;

    for (auto& it : players){
      bool collision = npcMap.at(id)->checkCollision(*it.second);
      if (collision){
          npcMap.at(id)->position.x = auxXPos;
          npcMap.at(id)->position.y = auxYPos;
          return;
      }
    }

    for (auto &it : margins){
      bool collision = npcMap.at(id)->checkCollision(*it);
      if (collision){
        npcMap.at(id)->position.x = auxXPos;
        npcMap.at(id)->position.y = auxYPos;
        return;
      }
    }

    for (auto& it : npcMap){
      if (npcMap.at(it.first)->id == id) continue;
      bool collision = npcMap.at(id)->checkCollision(*it.second);
      if (collision){
          npcMap.at(id)->position.x = auxXPos;
          npcMap.at(id)->position.y = auxYPos;
          return;
      }
    }
}

void GameModel::eraseClient(size_t playerID){
  players.erase(playerID);
  clientsBQ.erase(playerID);
}

void GameModel::propagate() {
  generateOtherPlayersGameData();
  generateNPCVector();

  std::unique_ptr<CronGameModelData> cronGameModelData(new CronGameModelData);
  cronGameModelData->npcs = npcs;
  cronGameModelData->otherPlayers = otherPlayers;
  cronBQ.push(std::move(cronGameModelData));

  for (auto& it : players){
    PlayerGameModelData modelData = {};

    generatePlayerModel(it.first, modelData);

    std::unique_ptr<Response> response(new
      PlayerGameResponse(modelData));

    clientsBQ.at(it.first).push(std::move(response));
  }
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  modelData.npcs = npcs;
  //modelData.map = map;

  modelData.playerData.nick = players.at(id)->nick;
  modelData.playerData.id = id;
  modelData.playerData.gold = players.at(id)->gold;
  modelData.playerData.levelAndExperience = 
    players.at(id)->levelAndExperience;
  modelData.playerData.skills = players.at(id)->skills;
  modelData.playerData.rootd = players.at(id)->rootd;
  modelData.playerData.inventory = players.at(id)->inventory;
  modelData.playerData.points = players.at(id)->health;
  modelData.playerData.position = players.at(id)->position;
  modelData.playerData.movement = players.at(id)->movement;
  modelData.playerData.equipment = players.at(id)->equipment;

  modelData.otherPlayers = otherPlayers;
}

void GameModel::generateOtherPlayersGameData(){
  otherPlayers.clear();
  for (auto& it : players){
    OtherPlayersData otherPlayer;
    otherPlayer.id = players.at(it.first)->id;
    otherPlayer.position = players.at(it.first)->position;
    otherPlayer.movement = players.at(it.first)->movement;
    otherPlayer.rootd = players.at(it.first)->rootd;
    otherPlayers.push_back(std::move(otherPlayer));
  }
}

void GameModel::generateNPCVector(){
  npcs.clear();
  for (auto& it : npcMap){
    EnemyData enemy;
    enemy.id = npcMap.at(it.first)->id;
    enemy.position = npcMap.at(it.first)->position;
    enemy.movement = npcMap.at(it.first)->movement;
    enemy.type = npcMap.at(it.first)->type;
    enemy.healthAndManaData = npcMap.at(it.first)->health;
    npcs.push_back(std::move(enemy));
  }
}

void GameModel::addNPCS(){
  // Código para generar id random, solo para mockear //
  
  struct EnemyData data;
  data.id = rand_r(&seed) % 100;
  data.position.x = 200;
  data.position.y = 100;
  data.position.w = 53;
  data.position.h = 35;
  data.movement.xDir = 0;
  data.movement.yDir = 1;
  data.type = SPIDER;
  data.healthAndManaData = {100, 100, 0, 0};
  SkillsData skills = {10, 10, 10};

  std::unique_ptr<NPC> spider(new NPC(data, skills));
  npcMap.insert(std::pair<size_t,
    std::unique_ptr<NPC>>(data.id, std::move(spider)));  

  data.id = rand_r(&seed) % 100;
  data.position.x = 200;
  data.position.y = 200;
  data.position.w = 53;
  data.position.h = 35;
  data.movement.xDir = 0;
  data.movement.yDir = 1;
  data.type = SPIDER;

  std::unique_ptr<NPC> spider2(new NPC(data, skills));
  npcMap.insert(std::pair<size_t,
  std::unique_ptr<NPC>>(data.id, std::move(spider2)));  
}
