#include "ChatController.h"

#include <iostream>

ChatController::ChatController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void ChatController::init() {
  LTexture* userInput = manager.getTexture("user-input");
  TTF_Font* font = manager.getFont("arial");


  userInputField = new TextInputEntity(
    userInput,
    font,
    CHAT_INPUT_X,
    CHAT_INPUT_Y,
    CHAT_INPUT_W,
    CHAT_INPUT_H);
  entities.emplace_back(userInputField);
  model.isAuthenticated();
}

void ChatController::handleEvent(const SDL_Event &e) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      active = inRect(src, e.button.x, e.button.y);
      userInputField->handleClick(
        e.button.x - src.x, e.button.y - src.y);
    }
  }
  if (!active) return;
  userInputField->handleInput(e);

  if (e.type == SDL_KEYDOWN &&
    e.key.keysym.sym == SDLK_RETURN) {
    handleCommand();
    userInputField->clearInput();
  }
}

void ChatController::handleCommand() {
  std::string command = userInputField->getInput();
  std::string delimiter = " ";
  size_t pos = command.find(" ");

  std::string action = command.substr(0, pos);
  std::cout << "ACTION: " <<  action << std::endl;
  command.erase(0, pos + delimiter.length());
  std::cout << "PARAMS: " << command << std::endl;
}

std::vector<Entity*> ChatController::getEntities() {
  return entities;
}
