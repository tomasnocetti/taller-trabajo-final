#include "GameModel.h"
#include "GameConfig.h"
#include <iostream>
#include <string> // TODO - Lo pide el parser
#include <utility>
#include <vector>
#include <random>
#include <stdlib.h>
#include <utility>
#include "services/ChatManager.h"
#include <map>

#define INIT_MAPCOORD_X 2600
#define INIT_MAPCOORD_Y 2600

GameModel::GameModel(CronBQ& cronBQ) :
  cronBQ(cronBQ),
  randomSeed(0){
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
          NPC::getNewId(), p, SPIDER));
        npcMap.insert(std::pair<size_t,
        std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));
      }

      if (layer.name == GOBLIN_SPAWN_POINTS){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, GOBLIN));
        npcMap.insert(std::pair<size_t,
        std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));
      }

      if (layer.name == SKELETON_SPAWN_POINTS){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, SKELETON));
        npcMap.insert(std::pair<size_t,
        std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));
      }

      if (layer.name == "zombie-spawn"){
        std::unique_ptr<NPC> npc(NPC::createNPC(
          NPC::getNewId(), p, ZOMBIE));
        npcMap.insert(std::pair<size_t,
        std::unique_ptr<NPC>>(NPC::idGenerator, std::move(npc)));
      }

      if (layer.name == CITY_LAYER){
        std::unique_ptr<Entity> city(
          new Entity(p));
        cities.push_back(std::move(city));
      }

      if (layer.name == PRIESTS_LAYER){
        std::unique_ptr<Priest> priest(
          new Priest(p));
        priests.insert(std::pair<size_t,
        std::unique_ptr<Priest>>(Priest::getNewId(), std::move(priest)));
      }

      if (layer.name == MERCHANT_LAYER){
        std::unique_ptr<Trader> trader(
          new Trader(p));
        traders.insert(std::pair<size_t,
        std::unique_ptr<Trader>>(Trader::getNewId(), std::move(trader)));
      }

      if (layer.name == BANKER_LAYER){
        std::unique_ptr<Banker> banker(
          new Banker(p));
        bankers.insert(std::pair<size_t,
        std::unique_ptr<Banker>>(Banker::getNewId(), std::move(banker)));
      }
    }
  }
}

GameModel::~GameModel(){}

bool GameModel::authenticate(
  std::string& password,
  std::string& nick,
  ResponseBQ& responseBQ,
  size_t& playerId) {
  // TODO: BUSCAR EN LOS ARCHIVOS. VER SI EXISTE Y OBTENER DATA//

  if (!f.authenticate(nick, password)) return false;

  PlayerPersistData p = f.getData(nick);
  playerId = p.id; //!IMPORTANTE SETEAR EL ID PARA LA COMUNICACION
  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//

  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(p.id, responseBQ));

  std::unique_ptr<Player> player(Player::createPlayer(p, nick));

  PositionData initialPos = {
    p.positionX,
    p.positionY, 
    PLAYER_WIDTH, 
    PLAYER_HEIGHT};
  getRespawnPosition(initialPos, *player);

  players.insert(std::pair<size_t,
    std::unique_ptr<Player>>(playerId, std::move(player)));

  responseBQ.push(
    std::unique_ptr<MapResponse> (new MapResponse(m.getMapData())));
  return true;
}

bool GameModel::createPlayer(
  ResponseBQ& responseBQ,
  size_t& playerId,
  std::string nick, 
  std::string password, 
  PlayerClass classType,
  PlayerRace race){
    switch (race){
      case HUMAN:
      case ELF:
      case GNOME:
      case DWARF:
        break;   
      default:
        std::cout << "Error al crear al jugador" << std::endl;
        return false;
    }
    switch (classType){
      case MAGE:
      case CLERIC:
      case PALADIN:
      case WARRIOR:
        break;
      default:
        std::cout << "Error al crear al jugador" << std::endl;
        return false;
    }
    
    if (f.checkIfNickExists(nick)){
      std::cout << "El nick ya existe." << std::endl;
      return false;
    } 

    PositionData position = {2600, 2600, 0, 0};
    f.create(nick, password, {classType, race}, position);

    authenticate(password, nick, responseBQ, playerId);
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
  
  if (p.specialAttack(xPos, yPos)) return;

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
    gameSound = {p.equipment.rightHand, xPos, yPos};
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
    
    gameSound = {p.equipment.rightHand, xPos, yPos};

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
    collission = entity.checkCollision(*it.second);
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
    double distance = p.getPositionDistance(it.second->position, p.position);
    if (distance >= minDistanceToPriest && minDistanceToPriest != 0) continue;
    minDistanceToPriest = distance;
    resurrectionPos = it.second->position;
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
  const GlobalConfig& c = GC::get(); 
  InventoryElementData itemToDrop;
  PositionData dropFirstPos;
  
  p.stopMeditating();
  
  bool success = p.throwObj(inventoryPosition, itemToDrop, dropFirstPos);
  if (!success) return;

  dropFirstPos.w = c.dropZoneWidth;
  dropFirstPos.h = c.dropZoneHeight;

  DropItemData item = {dropFirstPos, 1, itemToDrop.itemId};
  getDropPosition(item.position);
  drops.push_back(std::move(item));
}

void GameModel::pickUpObj(size_t playerId){
  Player &p = *players.at(playerId);
  const GlobalConfig& c = GC::get();
  
  if (!p.isAlive()) return;

  drops.erase(
    std::remove_if(
      drops.begin(), 
      drops.end(),
      [&p, &c](DropItemData &it) {
        int goldPlayerBeforeDrop = p.gold;

        bool success = p.pickUp(it);
        if (!success) return false;

        if (it.id == c.goldItemId){
          it.amount -= (p.gold - goldPlayerBeforeDrop);
          if (it.amount != 0) return false;
        }
        return true;
  }), drops.end());
}

void GameModel::list(size_t playerId){
  Player &p = *players.at(playerId);

  int traderId = checkTraderInRange(p);
  int priestId = checkPriestInRange(p);
  int bankerId = checkBankerInRange(p);

  if (traderId == -1 && priestId == -1 && bankerId == -1) return; 
  // escribir mensaje en el player

  if (traderId != -1){
    traders.at(traderId)->listItems(p);
    return;
  }

  if (priestId != -1){
    priests.at(priestId)->listItems(p);
    return;
  }

  bankers.at(bankerId)->listItems(p);
}

int GameModel::checkPriestInRange(Player &p){
  const GlobalConfig& c = GC::get();

  for (auto &it : priests){
    bool inRange = priests.at(it.first)->checkInRange(
      p,
      c.traderBankerPriestMinRangeToInteract);
    if (inRange) return it.first;
  } 
  return -1;
}

int GameModel::checkTraderInRange(Player &p){
  const GlobalConfig& c = GC::get();

  for (auto &it : traders){
    bool inRange = traders.at(it.first)->checkInRange(
      p,
      c.traderBankerPriestMinRangeToInteract);
    if (inRange) return it.first;
  } 
  return -1;
}

int GameModel::checkBankerInRange(Player &p){
  const GlobalConfig& c = GC::get();

  for (auto &it : bankers){
    bool inRange = bankers.at(it.first)->checkInRange(
      p,
      c.traderBankerPriestMinRangeToInteract);
    if (inRange) return it.first;
  } 
  return -1;
}

void GameModel::sell(size_t playerId, size_t itemPosition){
  const GlobalConfig& c = GC::get();
  Player &p = *players.at(playerId);
  int traderId = checkTraderInRange(p);

  if (traderId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandSell);
    return;
  }

  traders.at(traderId)->buy(p, itemPosition - 1);
}

void GameModel::buy(size_t playerId, size_t itemPosition){
  const GlobalConfig& c = GC::get(); 
  Player &p = *players.at(playerId);
 
  int traderId = checkTraderInRange(p);
  int priestId = checkPriestInRange(p);

  if (traderId == -1 && priestId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandBuy);
    return;
  }

  if (traderId != -1){
    traders.at(traderId)->sell(itemPosition, p);
    return;
  }

  priests.at(priestId)->sell(itemPosition, p);
}

void GameModel::heal(size_t playerId){
  const GlobalConfig& c = GC::get(); 
  Player &p = *players.at(playerId);
  
  int priestId = checkPriestInRange(p);
  if (priestId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandHeal);
    return;
  }
  p.heal();
}

void GameModel::depositGold(size_t playerId, size_t amount){
  const GlobalConfig& c = GC::get(); 
  Player &p = *players.at(playerId);

  int bankerId = checkBankerInRange(p);
  if (bankerId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandDepositWithdraw);
    return;
  }
  bankers.at(bankerId)->depositGold(p, amount);
}

void GameModel::depositItem(size_t playerId, size_t inventoryPos){
  const GlobalConfig& c = GC::get(); 
  Player &p = *players.at(playerId);

  int bankerId = checkBankerInRange(p);
  if (bankerId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandDepositWithdraw);
    return;
  }
  bankers.at(bankerId)->deposit(p, inventoryPos);
}

void GameModel::withdrawGold(size_t playerId, size_t amount){
  const GlobalConfig& c = GC::get(); 
  Player &p = *players.at(playerId);
  
  int bankerId = checkBankerInRange(p);
  if (bankerId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandDepositWithdraw);
    return;
  }
  bankers.at(bankerId)->withDrawGold(p, amount);
}

void GameModel::withdrawItem(size_t playerId, size_t inventoryPos){
  const GlobalConfig& c = GC::get(); 
  Player &p = *players.at(playerId);

  int bankerId = checkBankerInRange(p);
  if (bankerId == -1){
    p.sendMessage(INFO, c.chatMessages.invalidCommandDepositWithdraw);
    return;
  }

  bankers.at(bankerId)->withdraw(p, inventoryPos);
}

void GameModel::sendMessageToPlayer(
  size_t &id, 
  std::string &nick, 
  std::string &message){
    const GlobalConfig& c = GC::get(); 
    Player &p = *players.at(id);
  
    size_t addresseeId;
    bool addresseeExist = f.getPlayerId(nick, addresseeId);
    if (!addresseeExist){
      p.sendMessage(NORMAL, c.chatMessages.playerDoesNotExit);
      return;
    }

    std::map<size_t, std::unique_ptr<Player>>::iterator it;
    it = players.find(addresseeId);
    if (it == players.end()){
      p.sendMessage(NORMAL, c.chatMessages.playerNotOnline);
      return;
    }    
    
    p.sendMessage(NORMAL, "Yo: " + message);
    players.at(addresseeId)->sendMessage(NORMAL, p.nick + ": " + message);
}

void GameModel::commandError(size_t playerId){
  const GlobalConfig& c = GC::get(); 
  players.at(playerId)->sendMessage(INFO, c.chatMessages.invalidCommand);
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
  Player& p = *players.at(playerID);
  PlayerPersistData d = p.generatePersistData();
  f.saveData(p.nick, d);
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

  disableSound();
}

void GameModel::disableSound(){
  gameSound = {0, 0, 0};
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  modelData.npcs = npcs;
  modelData.drops = drops;
  players.at(id)->setPlayerGameModelData(modelData);
  modelData.otherPlayers = otherPlayers;
  modelData.gameSound = gameSound;
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
