#include "CronInstructions.h"

#include <iostream>

PlayerSetCoordsInstruction::PlayerSetCoordsInstruction(size_t id,
  int x, int y) :
  playerId(id),
  x(x),
  y(y) {}

void PlayerSetCoordsInstruction::run(GameModel& game) {
  std::cout << "SET COORDS "
    << playerId << "A x: " << x << " y: " << y << std::endl;
  game.playerSetCoords(playerId, x, y);
}
