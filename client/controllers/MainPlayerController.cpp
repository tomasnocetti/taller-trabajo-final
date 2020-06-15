#include "MainPlayerController.h"

#define MANA_BAR_Y 58
#define HEALTH_BAR_Y 109

MainPlayerController::MainPlayerController(
  ClientProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void MainPlayerController::init(){
  manager.addTexture("player-view", "client/assets/playerView.png");
  manager.addTexture("health", "client/assets/health.png");
  manager.addTexture("mana", "client/assets/mana.png");

  MainPlayerData data = model.getMainPlayerData();
  int x = data.position.x;
  int y = data.position.y;

  playerView.init(
    manager.getTexture("player-view"), x, y);
  healthBar.init(manager.getTexture("health"), HEALTH_BAR_Y);
  manaBar.init(manager.getTexture("mana"), MANA_BAR_Y);
  gold.init(manager.createTexture(), std::to_string(data.gold));
}

void MainPlayerController::update() {
  MainPlayerData data = model.getMainPlayerData();
  healthBar.update(data.points.currentHP, data.points.totalHP);
  manaBar.update(data.points.currentMP, data.points.totalMP);
  playerView.walk(data.position.x, data.position.y);
  gold.update(std::to_string(data.gold));
}

void MainPlayerController::handleEvent(const SDL_Event &e){
  switch (e.type){
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym){
        case SDLK_w:
          model.walk(0, -1);
        break;
        case SDLK_s:
          model.walk(0, 1);
        break;
        case SDLK_a:
          model.walk(-1, 0);
        break;
        case SDLK_d:
          model.walk(1, 0);
        break;
        case SDLK_f:
          model.a(100);
        break;
      }
    break;

    /*case SDL_KEYUP:
      switch (e.key.keysym.sym){
        case SDLK_w:
          model.stand(0, -1);
        break;
        case SDLK_s:
          model.stand(0, 1);
        break;
        case SDLK_a:
          model.stand(-1, 0);
        break;
        case SDLK_d:
          model.stand(1, 0);
        break;
      }
    break;*/
  }
}

Entity &MainPlayerController::getEntity(){
	return playerView;
}

std::vector<Entity*> MainPlayerController::getBars() {
  std::vector<Entity*> v;
  v.push_back(&this->healthBar);
  v.push_back(&this->manaBar);
  v.push_back(&this->gold);
  return v;
}

MainPlayerController::~MainPlayerController() {}
