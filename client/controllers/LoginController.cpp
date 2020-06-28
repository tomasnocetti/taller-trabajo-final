#include "LoginController.h"

#define LOGIN_SCREEN_PATH "client/assets/main-screens/login-screen.jpg"

LoginController::LoginController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void LoginController::init() {
  manager.addTexture("user-input", LOGIN_SCREEN_PATH);
  LTexture* baseScreen = manager.getTexture("login-screen-path");
  LTexture* userInput = manager.getTexture("user-input");
  TTF_Font* font = manager.getFont("main");

  screens.emplace_back(new BackgroundEntity(baseScreen));

  userInputField = new TextInputEntity(userInput, font, 1 , 345, 262);
  screens.emplace_back(userInputField);
}

void LoginController::handleEvent(const SDL_Event &e) {
  userInputField->handleEvent(e);
  model.isAuthenticated();
}

EntityList& LoginController::getEntities() {
  return screens;
}
