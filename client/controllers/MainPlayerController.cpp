#include "MainPlayerController.h"
#include <iostream>
#include <vector>

#define MANA_BAR_Y 58
#define HEALTH_BAR_Y 109
#define GOLD_Y 10
#define GOLD_X 105

MainPlayerController::MainPlayerController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void MainPlayerController::init(){
  MainPlayerData data = model.getMainPlayerData();
  myMoveData.xDir = data.movement.xDir;
  myMoveData.yDir = data.movement.yDir;

  TTF_Font* font = manager.getFont("main");
  LTexture* goldTexture = manager.getTexture("gold");

  playerView.init(
    manager.getTexture("clothes"), data.position.x, data.position.y);
  checkRace(data.rootd.prace);
  healthBar.init(manager.getTexture("health"), HEALTH_BAR_Y);
  manaBar.init(manager.getTexture("mana"), MANA_BAR_Y);
  gold.init(GOLD_X, GOLD_Y, goldTexture, font);
}

void MainPlayerController::update() {
  MainPlayerData data = model.getMainPlayerData();
  myMoveData.xDir = data.movement.xDir;
  myMoveData.yDir = data.movement.yDir;
  playerView.move(data.position.x, data.position.y);

  healthBar.update(data.points.currentHP, data.points.totalHP);
  manaBar.update(data.points.currentMP, data.points.totalMP);
  gold.update(std::to_string(data.gold));
}

void MainPlayerController::handleEvent(const SDL_Event &e,
  int cameraX, int cameraY) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      model.attack(e.button.x + cameraX - 11, e.button.y + cameraY - 154);
    }
  }

  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
			case SDLK_w:
				model.move(0, -1);
        break;
			case SDLK_s:
        model.move(0, 1);
				break;
			case SDLK_a:
        model.move(-1, 0);
				break;
			case SDLK_d:
        model.move(1, 0);
				break;
		}
    return;
  }

  if (e.type == SDL_KEYUP) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (!currentKeyStates[SDL_SCANCODE_W] &&
      !currentKeyStates[SDL_SCANCODE_S] &&
      !currentKeyStates[SDL_SCANCODE_A] &&
      !currentKeyStates[SDL_SCANCODE_D]) {
      model.move(0, 0);
    }
    return;
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

void MainPlayerController::checkRace(PlayerRace race) {
  switch (race){
    case DWARF:
      playerView.setHead(manager.getTexture("dwarf-head"));
    break;
    case ELF:
      playerView.setHead(manager.getTexture("elf-head"));
    break;
    case HUMAN:
      playerView.setHead(manager.getTexture("human-head"));
    break;
    case GNOME:
      playerView.setHead(manager.getTexture("gnome-head"));
    break;
    default:
    break;
  }
}

MainPlayerController::~MainPlayerController() {}
