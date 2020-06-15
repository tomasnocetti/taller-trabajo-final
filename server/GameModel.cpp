#include "GameModel.h"
#include <iostream>

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
  players.push_back(std::move(player));
  
  std::cout << "Id " << instruction.playerId << " cargado exitosamente." 
    << std::endl;

  return true;
}

bool GameModel::move(InstructionData &instruction){
  size_t id = instruction.playerId;
  size_t i = 0, j = 0;
  bool canMove = true;

  while (i < players.size()){
    if (players.at(i)->id == id){
      while (j < players.size() && canMove){
        canMove = players.at(i)->checkCollision(*players.at(j));
        j++;
      }
    if (canMove)
      players.at(i)->move(instruction.params.at(0).value, 
        instruction.params.at(1).value);
    }
    i++;
  }

  std::cout << "Mover jugador a x:" << instruction.params.at(0).value 
  << " y:" << instruction.params.at(1).value << std::endl;
  return canMove;
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  size_t i = 0;

  //modelData.npcs = npcs;
  //modelData.map = map;
  
  while (i < players.size()){
    if (players.at(i)->id == id){
      modelData.playerData.gold = players.at(i)->gold;
      modelData.playerData.health = players.at(i)->health;
      modelData.playerData.inventory = players.at(i)->inventory;
      modelData.playerData.level = players.at(i)->level;
      modelData.playerData.manaPoints = players.at(i)->manaPoints;
      modelData.playerData.position = players.at(i)->position;
      modelData.playerData.root = players.at(i)->root;
    }else{
      OtherPlayersData otherPlayer;
      
      otherPlayer.id = players.at(i)->id;
      otherPlayer.otherPlayerPosition = players.at(i)->position;
      otherPlayer.otherPlayerRoot = players.at(i)->root;
      
      modelData.otherPlayers.push_back(std::move(otherPlayer));
    }
    i++;
  }
}
