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

      if (layer.name == PRIESTS_LAYER){
        std::unique_ptr<Entity> priest(
          new Entity(p));
        priests.push_back(std::move(priest));
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
  Player& p = *players.at(playerId);
  if (p.health.currentHP <= 0) return;

  for (auto &it : cities)
    if (p.checkCollision(*it)) return;

  for (auto& it : players){
    for (auto &itCities : cities)
      if (players.at(it.first)->checkCollision(*itCities)) return;

    if (players.at(it.first)->health.currentHP <= 0) continue;

    if (players.at(it.first)->id == playerId) continue;

    if (!p.checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    bool success = p.attack(*it.second, xPos, yPos);

    if (success) break;
  }

  for (auto& it : npcMap){
    NPC& npc = *npcMap.at(it.first);

    if (!p.checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    bool success = p.attack(*it.second, xPos, yPos);
    if (!success) continue;

    if (npc.health.currentHP <= 0)
      npc.setNextRespawn();

    p.gold += npc.drop(randomSeed);
    return;
  }
}

void GameModel::playerSetCoords(size_t playerId, int x, int y) {
  Player& p = *players.at(playerId);  
  int auxXPos = p.position.x;
  int auxYPos = p.position.y;
  p.position.x = x;
  p.position.y = y;

  bool collision = checkPlayerCollissions(playerId);
  if (collision){
    p.position.x = auxXPos;
    p.position.y = auxYPos;
    return;
  }

  for (auto &it : margins){
    bool collision = p.checkCollision(*it);
    if (collision){
      p.position.x = auxXPos;
      p.position.y = auxYPos;
      return;
    }
  }
}

bool GameModel::checkPlayerCollissions(
  size_t playerId){
    Player& p = *players.at(playerId); 

    for (auto& it : players){
      if (players.at(it.first)->id == playerId) continue;
      bool collision = p.checkCollision(*it.second);
      if (collision) return true;
    }

    for (auto& it : npcMap){
      bool collision = npcMap.at(it.first)->checkCollision(*players[playerId]);
      if (collision) return true;
    }

    for (auto &it : priests){
      bool collission = p.checkCollision(*it);
      if (collission) return true;
    }

    return false;
}

void GameModel::equipPlayer(size_t playerId, int inventoryPosition){
  if (players.at(playerId)->health.currentHP <= 0) return;
  players.at(playerId)->equip(inventoryPosition);
}

void GameModel::resurrect(size_t playerId){
  Player &p = *players.at(playerId);
  if (p.health.currentHP > 0) return;

  double minDistanceToPriest = 0;
  PositionData resurrectionPos = {};

  for (auto& it : priests){
    double distance = p.getPositionDistance(it->position, p.position);
    if (distance >= minDistanceToPriest && minDistanceToPriest != 0) continue;
      minDistanceToPriest = distance;
      resurrectionPos = it->position;
  } 
  
  bool collision = true;
  while (collision){
    p.position.x = resurrectionPos.x + Equations::random(50, 80);
    p.position.y = resurrectionPos.y + Equations::random(50, 80);
    collision = checkPlayerCollissions(playerId);
  }

  p.setTimeToResurrect(minDistanceToPriest);
}

void GameModel::resurrectPlayer(size_t playerId){
  players.at(playerId)->resurrection.resurrect = false;
  players.at(playerId)->health.currentHP = 
    players.at(playerId)->health.totalHP;
}

void GameModel::npcSetCoords(size_t id, int xPos, int yPos){  
    NPC& n = *npcMap.at(id);
    int auxXPos = n.position.x;
    int auxYPos = n.position.y;
    
    n.position.x = xPos;
    n.position.y = yPos;

    for (auto& it : players){
      bool collision = n.checkCollision(*players[it.first]);
      if (collision){
          n.position.x = auxXPos;
          n.position.y = auxYPos;
          return;
      }
    }

    for (auto &it : cities){
      bool collision = n.checkCollision(*it);
      if (collision){
        n.position.x = auxXPos;
        n.position.y = auxYPos;
        return;
      }
    }

    for (auto &it : margins){
      bool collision = n.checkCollision(*it);
      if (collision){
        n.position.x = auxXPos;
        n.position.y = auxYPos;
        return;
      }
    }

    for (auto& it : npcMap){
      if (n.id == id) continue;
      bool collision = npcMap.at(it.first)->checkCollision(*npcMap[id]);
      if (collision){
          n.position.x = auxXPos;
          n.position.y = auxYPos;
          return;
      }
    }
}

void GameModel::npcAttack(size_t npcId, int xPos, int yPos){
  NPC& n = *npcMap.at(npcId);
  for (auto& it : players){
    for (auto &itCities : cities)
      if (players.at(it.first)->checkCollision(*itCities)) return;

    if (!n.checkInRange(*it.second, MAX_RANGE_ZONE))
        return;
    n.attack(*it.second, xPos, yPos);
  }
}

void GameModel::npcRespawn(size_t npcId){
  npcMap.at(npcId)->position = npcMap.at(npcId)->spawnPosition;
  npcMap.at(npcId)->health.currentHP = npcMap.at(npcId)->health.totalHP;
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
    otherPlayer.resurrection = players.at(it.first)->resurrection;
    otherPlayers.push_back(std::move(otherPlayer));
  }
}

void GameModel::generateNPCVector(){
  npcs.clear();
  for (auto& it : npcMap){
    NPC &npc = *npcMap.at(it.first);
    EnemyData enemy;
    enemy.movement = npc.movement;
    enemy.position = npc.position;
    enemy.type = npc.type;
    enemy.id = npc.id;
    enemy.healthAndManaData = npc.health;
    enemy.lastAttack = npc.lastAttack;
    npcs.push_back(std::move(enemy));
  }
}
