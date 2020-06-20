#include "GameModel.h"

#include <iostream>
#include <string> // TODO - Lo pide el parser
#include <utility>
#include <vector>

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
  MainPlayerData playerData = {{WARRIOR, HUMAN}, {""}, {0, 0},
  {0, 0, 0, 0}, {0, 0, 0}};

  if (nick == "Fer") playerId = 1;
  if (nick == "Tomi") playerId = 2;

  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//
  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(playerId, responseBQ));

  std::unique_ptr<Player> player(new Player(playerData, playerId));
  players.insert(std::pair<size_t,
    std::unique_ptr<Player>>(playerId, std::move(player)));

  std::cout << "Id " << players.at(playerId)->id <<
   " cargado exitosamente." << std::endl;

  return true;
}

void GameModel::move(size_t playerId, int x, int y) { }

void GameModel::playerSetCoords(size_t playerId, int x, int y) {
  // bool canMove = true;

  /** SEARCH PLAYER */

  // MainPlayerData playerProxyData;
  // Player playerproxy(playerProxyData, -1);

  // playerproxy.move(instruction.params.at(0).value,
  //   instruction.params.at(1).value);

  // for (auto&it : players){
  //   if (it.first == instruction.playerId) continue;
  //   canMove = playerproxy.checkCollision(*it.second);
  // }

  // std::cout << canMove << std::endl;

  // if (!canMove) return canMove;

  // players.at(instruction.playerId)->move(instruction.params.at(0).value,
  //   instruction.params.at(1).value);

  // return canMove;
}

void GameModel::propagate() {
  generateOtherPlayersGameData();
  for (auto& it : players){
    PlayerGameModelData modelData = {};

    generatePlayerModel(it.first, modelData);

    std::unique_ptr<Response> response(new
      PlayerGameResponse(modelData));

    clientsBQ.at(it.first).push(std::move(response));
  }
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  //modelData.npcs = npcs;
  //modelData.map = map;

  modelData.playerData.gold = players.at(id)->gold;
  modelData.playerData.points = players.at(id)->health;
  modelData.playerData.inventory = players.at(id)->inventory;
  modelData.playerData.level = players.at(id)->level;
  modelData.playerData.position = players.at(id)->position;
  modelData.playerData.rootd = players.at(id)->root;

  modelData.otherPlayers = otherPlayers;
}

void GameModel::generateOtherPlayersGameData(){
  otherPlayers.clear();
  for (auto& it : players){
    OtherPlayersData otherPlayer;
    otherPlayer.id = players.at(it.first)->id;
    otherPlayer.position = players.at(it.first)->position;
    otherPlayer.rootd = players.at(it.first)->root;
    otherPlayers.push_back(std::move(otherPlayer));
  }
}
