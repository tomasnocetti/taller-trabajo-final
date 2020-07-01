#include "CronInstructions.h"

#include <iostream>

PlayerSetCoordsInstruction::PlayerSetCoordsInstruction(size_t id,
  int x, int y) :
  playerId(id),
  x(x),
  y(y) {}

void PlayerSetCoordsInstruction::run(GameModel& game) {
  game.playerSetCoords(playerId, x, y);
}

NPCSetCoordsInstruction::NPCSetCoordsInstruction(size_t id,
  int xPos, int yPos) :
  npcId(id),
  xPos(xPos),
  yPos(yPos) {}

void NPCSetCoordsInstruction::run(GameModel& game) {
  game.npcSetCoords(npcId, xPos, yPos);
}

NPCAttackInstruction::NPCAttackInstruction(size_t id,
  int xPos, int yPos) :
  npcId(id),
  xPos(xPos),
  yPos(yPos) {}

void NPCAttackInstruction::run(GameModel& game) {
  game.npcAttack(npcId, xPos, yPos);
}

NPCRespawnInstruction::NPCRespawnInstruction(size_t id) :
  npcId(id) {}

void NPCRespawnInstruction::run(GameModel& game) {
  game.npcRespawn(npcId);
}

PlayerResurrecctionInstruction::PlayerResurrecctionInstruction(size_t id) :
    playerId(id){}

void PlayerResurrecctionInstruction::run(GameModel& game) {
  game.resurrectPlayer(playerId);
}

PlayerIncreaseHealthInstruction::PlayerIncreaseHealthInstruction(size_t id) :
    playerId(id){}

void PlayerIncreaseHealthInstruction::run(GameModel& game) {
  game.increasePlayerHealth(playerId);
}

PlayerIncreaseManaInstruction::PlayerIncreaseManaInstruction(size_t id) :
    playerId(id){}

void PlayerIncreaseManaInstruction::run(GameModel& game) {
  game.increasePlayerMana(playerId);
}

IncreaseManaMeditationInstruction::IncreaseManaMeditationInstruction(
  size_t id) :
    playerId(id){}

void IncreaseManaMeditationInstruction::run(GameModel& game) {
  game.increaseManaByMeditation(playerId);
}
