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

  screens.emplace_back(new TextInputEntity(userInput, font, 345, 262));
}


EntityList& LoginController::getEntities() {
  return screens;
}
