#include "GlobalController.h"
#include <SDL2/SDL_mixer.h>

GlobalController::GlobalController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void GlobalController::init() {
  LTexture* baseScreen = manager.getTexture("main-screen-path");
  screens.emplace_back(new BackgroundEntity(baseScreen));
}

void GlobalController::update() {
  if (!model.isAuthenticated()) return;
  
  if(Mix_PlayingMusic() == 0){
    Mix_Music* music = manager.getMusic("main-music");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    Mix_PlayMusic(music, -1);
  }
}

EntityList& GlobalController::getEntities() {
  return screens;
}
