#include "LoginController.h"

LoginController::LoginController(
  ClientProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void LoginController::init() {
  manager.addTexture("login-screen-path", LOGIN_SCREEN_PATH);
  LTexture* baseScreen = manager.getTexture("login-screen-path");
  screens.emplace_back(new BackgroundEntity(baseScreen));
}

EntityList& LoginController::getEntities() {
  return screens;
}
