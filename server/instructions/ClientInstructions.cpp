#include "Instruction.h"

#include <iostream>

MoveInstruction::MoveInstruction(size_t id) :
  playerId(id) {}

void MoveInstruction::run(GameModel& game) {
  std::cout << "MOVIENDO " << playerId << std::endl;
  // game.move(playerId, x, y);
}

AuthInstruction::AuthInstruction(ClientProxy& client, std::string nick) :
  client(client), nick(nick) {}

void AuthInstruction::run(GameModel& game) {
  std::cout << "AUTENTIFICANDO " << nick << std::endl;

  size_t playerId;
  bool success = game.authenticate(nick, client.getUpdateBQ(), playerId);

  if (success) {
    std::cout << "AUTENTIFICADO " << playerId << std::endl;
    client.setPlayerId(playerId);
    return;
  }
}

CloseInstruction::CloseInstruction(size_t id) :
  playerId(id) {}

void CloseInstruction::run(GameModel& game) {
  std::cout << "Despidiendo al jugador de id " << playerId << std::endl;
  // game.eraseClient(playerId)
}