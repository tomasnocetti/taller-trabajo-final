#include "MainPlayerController.h"

MainPlayerController::MainPlayerController(
  ClientProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void MainPlayerController::init(){
  manager.addTexture("player-view", "client/assets/playerView.png");

  playerView.init(
    manager.getTexture("player-view"),
    (542 - 11) / 2, (413 - 154) / 2);
}

void MainPlayerController::handleEvent(const SDL_Event &e){
	switch (e.type){
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym){
        case SDLK_w:
          playerView.walk(0, -1);
        break;
        case SDLK_s:
          playerView.walk(0, 1);
        break;
        case SDLK_a:
          playerView.walk(-1, 0);
        break;
        case SDLK_d:
          playerView.walk(1, 0);
        break;
      }
    break;

    case SDL_KEYUP:
      switch (e.key.keysym.sym){
        case SDLK_w:
          playerView.stand(0, -1);
        break;
        case SDLK_s:
          playerView.stand(0, 1);
        break;
        case SDLK_a:
          playerView.stand(-1, 0);
        break;
        case SDLK_d:
          playerView.stand(1, 0);
        break;
      }
    break;
  }
}

Entity &MainPlayerController::getEntity(){
	return playerView;
}

MainPlayerController::~MainPlayerController() {}
