#include "ChatController.h"

#include <iostream>
#include <string>

ChatController::ChatController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager){}

void ChatController::init() {
  LTexture* userInput = manager.getTexture("user-input");
  TTF_Font* font = manager.getFont("arial");

  userChatArea = std::shared_ptr<ChatArea> (
    new ChatArea(
      manager,
      CHAT_CONTENT_X,
      CHAT_CONTENT_Y,
      CHAT_CONTENT_W,
      CHAT_CONTENT_H,
      CHAT_PADDING_V,
      CHAT_LINE_HEIGHT));
  entities.emplace_back(userChatArea);
  userInputField =
    std::shared_ptr<TextInputEntity> (
      new TextInputEntity(
        userInput,
        font,
        CHAT_INPUT_X,
        CHAT_INPUT_Y,
        CHAT_INPUT_W,
        CHAT_INPUT_H));
  entities.emplace_back(userInputField);
}

void ChatController::update() {
  MainPlayerData data = model.getMainPlayerData();
  ChatData& chat = data.chat;
  userChatArea->update(chat);
}

void ChatController::handleEvent(const SDL_Event &e) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      active = inRect(src, e.button.x, e.button.y);
      userInputField->handleClick(
        e.button.x - src.x, e.button.y - src.y);
      userChatArea->handleClick(
        e.button.x - src.x, e.button.y - src.y);
    }
  }
  if (e.type == SDL_MOUSEBUTTONUP) {
    userChatArea->handleClickClear();
  }
  if (!active) return;
  userInputField->handleInput(e);

  if (e.type == SDL_KEYDOWN &&
    e.key.keysym.sym == SDLK_RETURN) {
    active = false;
    handleCommand();
    userInputField->clearInput();
  }
}

void ChatController::handleCommand() {
  std::string command = userInputField->getInput();
  std::string delimiter = " ";
  size_t pos = command.find(" ");

  /** INFO COMMAND **/
  std::string action = command.substr(0, pos);

  if (action == "/resucitar") {
    model.resurrect();
  }

  if (action == "/meditar"){
    model.meditate();
  }

  if (action == "/iniciar"){
    std::string alias = command.erase(0, pos + delimiter.length());
    model.authentificate(alias);
  }

  if (action == "/tirar"){
    std::string inventoryPosition = command.erase(0, pos+delimiter.length());
    model.throwObject(inventoryPosition);
  }

  if (action == "/tomar"){
    model.pickUp();
  }
}

EntityList& ChatController::getEntities() {
  return entities;
}
