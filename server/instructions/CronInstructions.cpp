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
  int xPos, int yPos, int xDir, int yDir) :
  npcId(id),
  xPos(xPos),
  yPos(yPos),
  xDir(xDir),
  yDir(yDir) {}

void NPCSetCoordsInstruction::run(GameModel& game) {
  game.npcSetCoords(npcId, xPos, yPos, xDir, yDir);
}
