#include "MainPlayerController.h"

MainPlayerController::MainPlayerController() {}

void MainPlayerController::init(LTexture texture, int x, int y){
	//this->data.x = x;
	//this->data.y = y;
	playerView.init(x, y, std::move(texture));
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
