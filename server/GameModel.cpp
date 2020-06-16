#include "GameModel.h"
#include <iostream>
#include <utility>

GameModel::GameModel(){}

GameModel::~GameModel(){}

bool GameModel::handleInstruction(InstructionData &instruction){
ActionTypeT action = instruction.action;
  switch (action)
  {
    case LOAD_PLAYER:
      return loadPlayer(instruction);
      break;
    case MOVE:
      return move(instruction);
      break;
    case BUY:
      return true;
      break;
    case DEPOSIT_GOLD:
      return true;
      break;
    case DEPOSIT_ITEM: 
      return true;
      break;
    case ATTACK:
      return true;
      break;
    case CLOSE_SERVER:
      std::cout << "Se cerrará el server." << std::endl;
      return true;
      break;
    default:
      std::cout << "El jugador quiere realizar otra accion. " << std::endl;
      return true;
      break;
  }
}

bool GameModel::loadPlayer(InstructionData &instruction){
  /* Este main player data lo obtengo de los archivos. */
  MainPlayerData playerData = {{WARRIOR, HUMAN}, {""}, {0, 0}, 
  {0, 0, 0, 0}, 0, 0, 0};
  
  std::unique_ptr<Player> player(new Player(playerData, instruction.playerId));
  players.insert(std::pair<size_t, 
    std::unique_ptr<Player>>(instruction.playerId,std::move(player)));
  
  std::cout << "Id " << players.at(instruction.playerId)->id <<
   " cargado exitosamente." << std::endl;

  std::cout << "El tamaño del mapa de jugadores es " <<
    players.size() << std::endl;

  return true;
}

bool GameModel::move(InstructionData &instruction){
  bool canMove = true;

  MainPlayerData playerProxyData;
  Player playerproxy(playerProxyData, -1);

  playerproxy.move(instruction.params.at(0).value,
    instruction.params.at(1).value);

  for (auto&it : players){
    if (it.first == instruction.playerId) continue;
    canMove = playerproxy.checkCollision(*it.second);
  }

  std::cout << canMove << std::endl;

  if (!canMove) return canMove;

  players.at(instruction.playerId)->move(instruction.params.at(0).value,
    instruction.params.at(1).value);

  return canMove;
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  //modelData.npcs = npcs;
  //modelData.map = map;
  if (players.count(id) > 0){
    modelData.playerData.gold = players.at(id)->gold;
    modelData.playerData.health = players.at(id)->health;
    modelData.playerData.inventory = players.at(id)->inventory;
    modelData.playerData.level = players.at(id)->level;
    modelData.playerData.manaPoints = players.at(id)->manaPoints;
    modelData.playerData.position = players.at(id)->position;
    modelData.playerData.root = players.at(id)->root;
  }
    
  modelData.otherPlayers = otherPlayers;
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
