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

      if (layer.name == "zombie-spawn"){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, 8, ZOMBIE));
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
  playerId  = Equations::random(1, 100);

  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//
  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(playerId, responseBQ));

  PlayerRootData root = {CLERIC, HUMAN};

  std::unique_ptr<Player> player(Player::createPlayer(playerId, nick, root));
  players.insert(std::pair<size_t,
    std::unique_ptr<Player>>(playerId, std::move(player)));

  responseBQ.push(
    std::unique_ptr<MapResponse> (new MapResponse(m.getMapData())));
  return true;
}

void GameModel::move(size_t playerId, int x, int y) {
  players.at(playerId)->movement.xDir = x;
  players.at(playerId)->movement.yDir = y;
}

void GameModel::stopMovement(size_t playerId){
  players.at(playerId)->stop();
}

bool GameModel::checkCityCollisions(Entity &entity){
  bool isInCity = false;
  for (auto &itCities : cities){
    isInCity = entity.checkCollision(*itCities);
    if (isInCity) break;
  }
  return isInCity;
}

void GameModel::attack(size_t playerId, int xPos, int yPos){
  Player& p = *players.at(playerId);
  const GlobalConfig& c = GC::get();
  if (p.health.currentHP <= 0) return;

  if (checkCityCollisions(p)) return;

  for (auto& it : players){
    if (p.level <= c.newbieLevel) break;

    Player& auxp = *players.at(it.first); 

    if (checkCityCollisions(auxp)) continue;

    if (abs((int)(p.level - auxp.level)) > (int)c.fairPlayLevel) continue;

    if (auxp.level <= c.newbieLevel) continue;

    if (auxp.health.currentHP <= 0) continue;

    if (auxp.id == playerId) continue;

    if (!p.checkInRange(*it.second, c.maxRangeZone))
      continue;

    bool success = p.attack(*it.second, xPos, yPos);
    if (!success) continue;

    p.stopMeditating();

    if (auxp.health.currentHP > 0) break;

    addPlayerDrops(auxp);
    auxp.drop();
    break;
  }

  for (auto& it : npcMap){
    NPC& npc = *npcMap.at(it.first);
    if (npc.health.currentHP <= 0) continue;

    if (!p.checkInRange(*it.second, c.maxRangeZone))
      continue;

    bool success = p.attack(*it.second, xPos, yPos);
    if (!success) continue;

    p.stopMeditating();

    if (npc.health.currentHP <= 0)
      npc.setNextRespawn();

    DropItemData drop;
    bool thereIsDrop = npc.drop(drop);
    if (!thereIsDrop) return;

    addNPCDrop(drop);
  }
}

void GameModel::addNPCDrop(DropItemData &drop){
  const GlobalConfig& c = GC::get();
  drop.position.w = c.dropSizes.weight;
  drop.position.h = c.dropSizes.height;

  getDropPosition(drop.position);
  drops.push_back(std::move(drop));
}

void GameModel::addPlayerDrops(Player &player){
  const GlobalConfig& c = GC::get();

  DropItemData goldDrop;
  goldDrop.id = c.goldItemId;
  goldDrop.position = player.position;
  goldDrop.position.w = c.dropSizes.weight;
  goldDrop.position.h = c.dropSizes.height;
  getDropPosition(goldDrop.position);
  goldDrop.amount = player.calculateExcessGold();
  if (goldDrop.amount > 0){
    drops.push_back(std::move(goldDrop));
    player.gold -= goldDrop.amount;
  }

  for (auto& it : player.inventory){
    DropItemData drop;
    drop.position = player.position;
    drop.position.w = c.dropSizes.weight;
    drop.position.h = c.dropSizes.height;
    drop.amount = it.amount;
    drop.id = it.itemId;
    getDropPosition(drop.position);
    drops.push_back(std::move(drop));
  }
}

void GameModel::getDropPosition(PositionData &positionToDrop){
  bool collision = true;
  const GlobalConfig& c = GC::get();
  int auxXPos = positionToDrop.x;
  
  for (int i = 1;; i++){
    positionToDrop.x += c.offsetToRespawn * i;
    collision = checkDropCollisions(positionToDrop);
    if (!collision) break;

    positionToDrop.x -= 2*(c.offsetToRespawn * i);
    collision = checkDropCollisions(positionToDrop);
    if (!collision) break;

    positionToDrop.x = auxXPos;
    positionToDrop.y += c.offsetToRespawn * i;
    collision = checkDropCollisions(positionToDrop);
    if (!collision) break;

    positionToDrop.y -= 2*(c.offsetToRespawn * i);
    collision = checkDropCollisions(positionToDrop);
    if (!collision) break;
  }
}

bool GameModel::checkDropCollisions(PositionData &dropPossiblePos){
  Entity possibleDrop(dropPossiblePos);

  for (auto& it : drops){
    Entity drop(it.position);
    if (drop.checkCollision(possibleDrop)) return true;
  }

  for (auto& it : margins){
    if (it->checkCollision(possibleDrop)) return true;
  }

  return false;
}

void GameModel::playerSetCoords(size_t playerId, int x, int y) {
  Player& p = *players.at(playerId);
  p.stopMeditating();

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
  Player &p = *players.at(playerId);
  
  p.stopMeditating();

  if (p.health.currentHP <= 0) return;
  
  p.equip(inventoryPosition);
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
    const GlobalConfig& c = GC::get();

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

void GameModel::recover(size_t playerId){
  Player &p = *players.at(playerId);
  p.recover();
}

void GameModel::meditate(size_t id){
  Player &p = *players.at(id);
  p.meditate();
}

void GameModel::throwInventoryObj(size_t playerId, size_t inventoryPosition){
  Player &p = *players.at(playerId);
  p.stopMeditating();
  p.throwObj(inventoryPosition);
}

void GameModel::pickUpObj(size_t playerId){
  Player &p = *players.at(playerId);
  bool success = false;
  
  for (auto& it : drops){
    success = p.pickUp(it);
    if (success) break;
  }
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

    if (checkCityCollisions(n)){
      n.position.x = auxXPos;
      n.position.y = auxYPos;
      return;
    }
}

void GameModel::npcAttack(size_t npcId, int xPos, int yPos){
  NPC& n = *npcMap.at(npcId);
  const GlobalConfig& c = GC::get();
  for (auto& it : players){
    Player &p = *it.second;
    if (p.health.currentHP < 0) return;
    
    if (checkCityCollisions(p)) continue;

    if (!n.checkInRange(*it.second, c.maxRangeZone))
        return;
    
    bool success = n.attack(*it.second, xPos, yPos);
    if (!success) continue;

    if (p.health.currentHP > 0) break;

    addPlayerDrops(*it.second);
    players.at(it.first)->drop();
    return;
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
  modelData.drops = drops;
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
