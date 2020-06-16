#include "MainPlayerController.h"

#define MANA_BAR_Y 58
#define HEALTH_BAR_Y 109
#define GOLD_Y 10
#define GOLD_X 105

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
  TTF_Font* font = manager.getFont("main");

  playerView.init(
    manager.getTexture("player-view"), x, y);
  healthBar.init(manager.getTexture("health"), HEALTH_BAR_Y);
  manaBar.init(manager.getTexture("mana"), MANA_BAR_Y);
  gold.init(GOLD_X, GOLD_Y, manager.createTexture(), font);
}

void MainPlayerController::update() {
  MainPlayerData data = model.getMainPlayerData();
  healthBar.update(data.points.currentHP, data.points.totalHP);
  manaBar.update(data.points.currentMP, data.points.totalMP);
  playerView.walk(data.position.x, data.position.y);
  gold.update(std::to_string(data.gold));
}

void MainPlayerController::handleEvent(const SDL_Event &e){
  if(e.type == SDL_MOUSEMOTION) return;

  const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
  if(currentKeyStates[SDL_SCANCODE_W]) {
    model.walk(0, -1);
  } else if(currentKeyStates[SDL_SCANCODE_S]) {
    model.walk(0, 1);
  } else if(currentKeyStates[SDL_SCANCODE_A]) {
    model.walk(-1, 0);
  } else if(currentKeyStates[SDL_SCANCODE_D]) {
    model.walk(1, 0);
  }
}

Entity &MainPlayerController::getEntity(){
	return playerView;
}

std::vector<Entity*> MainPlayerController::getBars() {
  std::vector<Entity*> v;
  v.push_back(&healthBar);
  v.push_back(&manaBar);
  v.push_back(&gold);
  return v;
}

MainPlayerController::~MainPlayerController() {}
