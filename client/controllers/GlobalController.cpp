#include "GlobalController.h"

GlobalController::GlobalController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void GlobalController::init() {
  LTexture* baseScreen = manager.getTexture("main-screen-path");
  screens.emplace_back(new BackgroundEntity(baseScreen));
}

EntityList& GlobalController::getEntities() {
  return screens;
}
