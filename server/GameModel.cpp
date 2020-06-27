#include "GameModel.h"

#include <iostream>
#include <string> // TODO - Lo pide el parser
#include <utility>
#include <vector>
#include <random>
#include <stdlib.h>

GameModel::GameModel(char* mapPath, CronBQ& cronBQ) :
  cronBQ(cronBQ),
  randomSeed(0){
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

      if (layer.name == SPIDER_SPAWN_POINTS){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, 10, SPIDER));
        npcMap.insert(std::pair<size_t,

          std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));  
      }

      if (layer.name == GOBLIN_SPAWN_POINTS){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, 15, GOBLIN));
        npcMap.insert(std::pair<size_t,

          std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));  
      }

      if (layer.name == SKELETON_SPAWN_POINTS){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, 8, SKELETON));
        npcMap.insert(std::pair<size_t,

          std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));  
      }

      if (layer.name == CITY_LAYER){
        std::unique_ptr<Entity> city(
          new Entity(p));
        cities.push_back(std::move(city));
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
  if (nick == "Fer") playerId  = rand_r(&randomSeed) % 100;

  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//
  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(playerId, responseBQ));

  PlayerRootData root = {CLERIC, HUMAN};

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
  if (players.at(playerId)->health.currentHP <= 0) return;

  for (auto &it : cities)
    if (players.at(playerId)->checkCollision(*it)) return;

  for (auto& it : players){
    for (auto &itCities : cities)
      if (players.at(it.first)->checkCollision(*itCities)) return;

    if (players.at(it.first)->id == playerId) continue;

    if (!players.at(playerId)->checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    bool success = players.at(playerId)->attack(*it.second, xPos, yPos);
    if (success) break;
  }

  for (auto& it : npcMap){
    if (!players.at(playerId)->checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    bool success = players.at(playerId)->attack(*it.second, xPos, yPos);

    if (!success) continue;

    players.at(playerId)->gold += npcMap.at(it.first)->drop(randomSeed);
    return;
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
    bool collision = npcMap.at(it.first)->checkCollision(*players[playerId]);
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
      bool collision = npcMap.at(id)->checkCollision(*players[it.first]);
      if (collision){
          npcMap.at(id)->position.x = auxXPos;
          npcMap.at(id)->position.y = auxYPos;
          return;
      }
    }

    for (auto &it : cities){
      bool collision = npcMap.at(id)->checkCollision(*it);
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
      bool collision = npcMap.at(it.first)->checkCollision(*npcMap[id]);
      if (collision){
          npcMap.at(id)->position.x = auxXPos;
          npcMap.at(id)->position.y = auxYPos;
          return;
      }
    }
}

void GameModel::npcAttack(size_t npcId, int xPos, int yPos){
  for (auto& it : players){
    for (auto &itCities : cities)
      if (players.at(it.first)->checkCollision(*itCities)) return;

    if (!npcMap.at(npcId)->checkInRange(*it.second, MAX_RANGE_ZONE))
        return;
    npcMap.at(npcId)->attack(*it.second, xPos, yPos);
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
  modelData.playerData.level = players.at(id)->level;
  modelData.playerData.experience = 
    players.at(id)->experience;
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
    otherPlayer.equipment = players.at(it.first)->equipment;
    otherPlayer.otherPlayerHealth = players.at(it.first)->health.currentHP;
    otherPlayers.push_back(std::move(otherPlayer));
  }
}

void GameModel::generateNPCVector(){
  npcs.clear();
  for (auto& it : npcMap){
    EnemyData enemy;
    enemy.movement = npcMap.at(it.first)->movement;
    enemy.position = npcMap.at(it.first)->position;
    enemy.type = npcMap.at(it.first)->type;
    enemy.id = npcMap.at(it.first)->id;
    enemy.healthAndManaData = npcMap.at(it.first)->health;
    npcs.push_back(std::move(enemy));
  }
}
