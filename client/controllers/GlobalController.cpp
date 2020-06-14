#include "GlobalController.h"

GlobalController::GlobalController(
  ClientProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void GlobalController::init() {
  manager.addTexture("main-screen-path", MAIN_SCREEN_PATH);
  LTexture* baseScreen = manager.getTexture("main-screen-path");
  screens.emplace_back(new BackgroundEntity(baseScreen));
}

EntityList& GlobalController::getEntities() {
  return screens;
}
