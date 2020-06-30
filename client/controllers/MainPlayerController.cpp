#include "MainPlayerController.h"
#include <iostream>
#include <vector>

#define MANA_BAR_Y 58
#define HEALTH_BAR_Y 109
#define EXP_BAR_Y 45
#define GOLD_Y 10
#define GOLD_X 105
#define LEVEL_X 50
#define LEVEL_Y 24

#define KEYCODE_OFFSET 48
#define KEYCODE_1 49
#define KEYCODE_9 57

MainPlayerController::MainPlayerController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager),
  playerView(manager) {}

void MainPlayerController::init(){
  MainPlayerData data = model.getMainPlayerData();

  TTF_Font* font = manager.getFont("arial");
  LTexture* healthText = manager.getTexture("healthText");
  LTexture* manaText = manager.getTexture("manaText");
  LTexture* goldText = manager.getTexture("goldText");
  LTexture* levelText = manager.getTexture("levelText");
  LTexture* expText = manager.getTexture("expText");
  
  playerView.init();
  healthBar.init(manager.getTexture("health"), HEALTH_BAR_Y,
    healthText, font);
  manaBar.init(manager.getTexture("mana"), MANA_BAR_Y, manaText, font);
  gold.init(GOLD_X, GOLD_Y, goldText, font);
  level.init(LEVEL_X, LEVEL_Y, levelText, font);
  expBar.init(manager.getTexture("exp"), EXP_BAR_Y, expText, font);
}

void MainPlayerController::update() {
  MainPlayerData data = model.getMainPlayerData();
  playerView.move(data.position.x, data.position.y);

  healthBar.update(data.points.currentHP, data.points.totalHP, 0);
  manaBar.update(data.points.currentMP, data.points.totalMP, 0);
  gold.update(std::to_string(data.gold));

  level.update(data.nick + " - nivel: " +
    std::to_string(data.level));
  expBar.update(data.experience.currentExperience,
    data.experience.maxLevelExperience,
    data.experience.minLevelExperience);

  playerView.checkRace(data.rootd.prace);
  playerView.checkHealth(data.points.currentHP);
  playerView.checkEquipment(data.equipment);
}

void MainPlayerController::handleEvent(const SDL_Event &e,
  int cameraX, int cameraY) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      if (!active) {
        active = inRect(src, e.button.x, e.button.y);
        return;
      }

      active = inRect(src, e.button.x, e.button.y);
      model.attack(
        e.button.x + cameraX - src.x,
        e.button.y + cameraY - src.y);
    }
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

  if (!active) return;

  if (e.type == SDL_KEYDOWN) {
    if (e.key.keysym.sym >= KEYCODE_1 && e.key.keysym.sym <= KEYCODE_9) {
      const char* keyName = SDL_GetKeyName(e.key.keysym.sym);
      int keyCode = static_cast<int>(*keyName);
      model.equip(keyCode - KEYCODE_OFFSET - 1);
      return;
    }
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

std::vector<Entity*> MainPlayerController::getExp() {
  std::vector<Entity*> v;
  v.push_back(&level);
  v.push_back(&expBar);
  return v;
}

MainPlayerController::~MainPlayerController() {}
