#include "Instruction.h"

#include <iostream>
#include <string>

MoveInstruction::MoveInstruction(size_t id, std::string xDir, 
  std::string yDir) :
    playerId(id),
    xDir(xDir),
    yDir(yDir) {}

void MoveInstruction::run(GameModel& game) {
  int x = stoi(xDir);
  int y = stoi(yDir);
  game.move(playerId, x, y);
}

AuthInstruction::AuthInstruction(ClientProxy& client, std::string nick) :
  client(client), nick(nick) {}

void AuthInstruction::run(GameModel& game) {
  size_t playerId;

  bool success = game.authenticate(nick, client.getUpdateBQ(), playerId);

  if (success) {
    client.setPlayerId(playerId);
    return;
  }
}

CloseInstruction::CloseInstruction(size_t id) :
  playerId(id) {}

void CloseInstruction::run(GameModel& game) {
  game.eraseClient(playerId);
}

StopMovementInstruction::StopMovementInstruction(size_t id) :
  playerId(id) {}

void StopMovementInstruction::run(GameModel& game) {
  game.stopMovement(playerId);
}

AttackInstrucion::AttackInstrucion(size_t id, std::string xPos, 
  std::string yPos) :
  playerId(id),
  xPos(stoi(xPos)),
  yPos(stoi(yPos)){}
  
void AttackInstrucion::run(GameModel& game) {
  game.attack(playerId, xPos, yPos);
}

EquipInstruction::EquipInstruction(size_t id, std::string inventoryPosition) :
  playerId(id),
  inventoryPosition(stoi(inventoryPosition)){}
  
void EquipInstruction::run(GameModel& game) {
  game.equipPlayer(playerId, inventoryPosition);
}

ResurrectInstrucion::ResurrectInstrucion(size_t id) :
  playerId(id){}

void ResurrectInstrucion::run(GameModel& game) {
  game.resurrect(playerId);
}

MeditateInstruction::MeditateInstruction(size_t id) :
  playerId(id){}

void MeditateInstruction::run(GameModel& game) {
  game.meditate(playerId);
}

ThrowObjInstruction::ThrowObjInstruction(size_t id, std::string inventoryPos) :
  playerId(id),
  inventoryPosition(std::stoi(inventoryPos)-1){}

void ThrowObjInstruction::run(GameModel& game) {
  game.throwInventoryObj(playerId, inventoryPosition);
}

PickUpInstruction::PickUpInstruction(size_t id) :
  playerId(id) {}

void PickUpInstruction::run(GameModel& game) {
  game.pickUpObj(playerId);
}

ListInstruction::ListInstruction(size_t id) :
  playerId(id) {}

void ListInstruction::run(GameModel& game) {
  game.list(playerId);
}

SellInstruction::SellInstruction(
  size_t id, std::string itemNumber) :
    playerId(id),
    itemNumber(std::stoi(itemNumber)){}

void SellInstruction::run(GameModel& game) {
  game.sell(playerId, itemNumber);
}

BuyInstruction::BuyInstruction(
  size_t id, std::string itemNumber) :
    playerId(id),
    itemNumber(std::stoi(itemNumber)-1){}

void BuyInstruction::run(GameModel& game) {
  game.buy(playerId, itemNumber);
}

HealInstruction::HealInstruction(size_t id) : playerId(id) {}

void HealInstruction::run(GameModel& game) {
  game.heal(playerId);
}
