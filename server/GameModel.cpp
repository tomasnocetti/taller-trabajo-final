#include "GameModel.h"
#include "GameConfig.h"
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
  GlobalConfig& c = GC::get();
  if (p.health.currentHP <= 0) return;

  for (auto &it : cities)
    if (p.checkCollision(*it)) return;

  for (auto& it : players){
    if (p.level <= c.newbieLevel) break;

    Player& auxp = *players.at(it.first); 

    for (auto &itCities : cities)
      if (auxp.checkCollision(*itCities)) return;

    if (abs((int)(p.level - auxp.level)) > (int)c.fairPlayLevel) continue;

    if (auxp.level <= c.newbieLevel) continue;

    if (auxp.health.currentHP <= 0) continue;

    if (auxp.id == playerId) continue;

    if (!p.checkInRange(*it.second, c.maxRangeZone))
      continue;

    bool success = p.attack(*it.second, xPos, yPos);
    if (success) break;
  }

  for (auto& it : npcMap){
    NPC& npc = *npcMap.at(it.first);

    if (!p.checkInRange(*it.second, c.maxRangeZone))
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

  bool collision = checkEntityCollisions(p);
  if (collision){
    p.position.x = auxXPos;
    p.position.y = auxYPos;
    return;
  }
}

bool GameModel::checkEntityCollisions(LiveEntity &entity){
  bool collission = true;
  for (auto& it : players){
    if (entity.id == players.at(it.first)->id) continue;
    collission = entity.checkCollision(*it.second);
    if (collission) return true;
  }

  for (auto& it : npcMap){
    if (entity.id == npcMap.at(it.first)->id) continue;
    collission = npcMap.at(it.first)->checkCollision(entity);
    if (collission) return true;
  }

  for (auto &it : priests){
    collission = entity.checkCollision(*it);
    if (collission) return true;
  }

  for (auto &it : margins){
    collission = entity.checkCollision(*it);
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
  getRespawnPosition(resurrectionPos, p);
  p.position = resurrectionPos;
  p.setTimeToResurrect(minDistanceToPriest);
}

void GameModel::getRespawnPosition(
  PositionData &positionToRes,
  LiveEntity &entity){
    bool collision = true;
    entity.position = positionToRes;
    GlobalConfig& c = GC::get();

    for (int i = 0;; i++){
      entity.position.x = positionToRes.x + c.offsetToRespawn * i;
      entity.position.y = positionToRes.y;
      collision = checkEntityCollisions(entity);
      if (!collision){
        positionToRes = entity.position;
        break;
      }
      entity.position.x = positionToRes.x;
      entity.position.y = positionToRes.y + c.offsetToRespawn * i;
      collision = checkEntityCollisions(entity);
      if (!collision){
        positionToRes = entity.position;
        break;
      }
    }
}

void GameModel::resurrectPlayer(size_t playerId){
  players.at(playerId)->resurrection.resurrect = false;
  players.at(playerId)->health.currentHP =
    players.at(playerId)->health.totalHP;
  players.at(playerId)->health.currentMP = 
    players.at(playerId)->health.totalMP;
}

void GameModel::increasePlayerHealth(size_t playerId){
  Player &p = *players.at(playerId);
  p.health.currentHP += p.skills.raceRecovery;
  p.health.lastHealthIncrease = std::chrono::system_clock::now();
  
  if (p.health.currentHP <= p.health.totalHP) return;
  p.health.currentHP = p.health.totalHP;
}

void GameModel::increasePlayerMana(size_t playerId){
  Player &p = *players.at(playerId);
  p.health.currentMP += p.skills.raceRecovery;
  p.health.lastManaIncrease = std::chrono::system_clock::now();
  
  if (p.health.currentMP <= p.health.totalMP) return;
  p.health.currentHP = p.health.totalHP;
}

void GameModel::npcSetCoords(size_t id, int xPos, int yPos){  
    NPC& n = *npcMap.at(id);
    int auxXPos = n.position.x;
    int auxYPos = n.position.y;
    n.position.x = xPos;
    n.position.y = yPos;

    bool collision = checkEntityCollisions(n);
    if (collision){
      n.position.x = auxXPos;
      n.position.y = auxYPos;
      return;
    }

    for (auto &it : cities){
      collision = n.checkCollision(*it);
      if (collision){
        n.position.x = auxXPos;
        n.position.y = auxYPos;
        return;
      }
    }
}

void GameModel::npcAttack(size_t npcId, int xPos, int yPos){
  NPC& n = *npcMap.at(npcId);
  GlobalConfig& c = GC::get();
  for (auto& it : players){
    for (auto &itCities : cities)
      if (players.at(it.first)->checkCollision(*itCities)) return;

    if (!n.checkInRange(*it.second, c.maxRangeZone))
        return;
    n.attack(*it.second, xPos, yPos);
  }
}

void GameModel::npcRespawn(size_t npcId){
  NPC &n = *npcMap.at(npcId);
  PositionData aux(n.spawnPosition);
  getRespawnPosition(n.spawnPosition, n);
  n.position = n.spawnPosition;
  n.health.currentHP = n.health.totalHP;
  n.spawnPosition = aux;
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

  PlayerGameModelData modelData = {};
  for (auto& it : players){
    generatePlayerModel(it.first, modelData);

    std::unique_ptr<Response> response(new
      PlayerGameResponse(modelData));

    clientsBQ.at(it.first).push(std::move(response));
  }
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  modelData.npcs = npcs;
  //modelData.map = map;
  players.at(id)->setPlayerGameModelData(modelData);
  modelData.otherPlayers = otherPlayers;
}

void GameModel::generateOtherPlayersGameData(){
  otherPlayers.clear();
  for (auto& it : players){
    OtherPlayersData otherPlayer;
    players.at(it.first)->setOtherPlayersData(otherPlayer);
    otherPlayers.push_back(std::move(otherPlayer));
  }
}

void GameModel::generateNPCVector(){
  npcs.clear();
  for (auto& it : npcMap){
    EnemyData enemy;
    npcMap.at(it.first)->setEnemyData(enemy);
    npcs.push_back(std::move(enemy));
  }
}
