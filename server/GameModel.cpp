#include "GameModel.h"
#include <iostream>
#include <utility>

GameModel::GameModel(){}

GameModel::~GameModel(){}

bool GameModel::authenticate(
  std::string& nick,
  ResponseBQ& responseBQ,
  size_t& playerId) {

  // TODO: BUSCAR EN LOS ARCHIVOS. VER SI EXISTE Y OBTENER DATA//
  playerId = 4;
  MainPlayerData playerData = {{WARRIOR, HUMAN}, {""}, {0, 0},
  {0, 0, 0, 0}, {0, 0, 0}};

  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//
  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(playerId, responseBQ));

  std::unique_ptr<Player> player(new Player(playerData, playerId));
  players.insert(std::pair<size_t,
    std::unique_ptr<Player>>(playerId, std::move(player)));

  std::cout << "Id " << players.at(playerId)->id <<
   " cargado exitosamente." << std::endl;

  return true;
}

void GameModel::move(size_t platerId, int x, int y) {
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
  // generateOtherPlayersGameData();
  // std::vector<size_t> playersId = activePlayers.getActivePlayers();
  // for (auto& it :playersId){
  //   PlayerGameModelData modelData = {};

  //   game.generatePlayerModel(it, modelData);
  //   activePlayers.updateModel(it, modelData);
  // }
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  //modelData.npcs = npcs;
  //modelData.map = map;
  // if (players.count(id) > 0){
  //   modelData.playerData.gold = players.at(id)->gold;
  //   modelData.playerData.health = players.at(id)->health;
  //   modelData.playerData.inventory = players.at(id)->inventory;
  //   modelData.playerData.level = players.at(id)->level;
  //   modelData.playerData.manaPoints = players.at(id)->manaPoints;
  //   modelData.playerData.position = players.at(id)->position;
  //   modelData.playerData.root = players.at(id)->root;
  // }

  // modelData.otherPlayers = otherPlayers;
}

void GameModel::generateOtherPlayersGameData(){
  OtherPlayersData otherPlayer;
  otherPlayers.clear();
  for (auto&it : players){
    otherPlayer.id = players.at(it.first)->id;
    otherPlayer.otherPlayerPosition = players.at(it.first)->position;
    otherPlayer.otherPlayerRoot = players.at(it.first)->root;
    otherPlayers.push_back(std::move(otherPlayer));
  }
}
