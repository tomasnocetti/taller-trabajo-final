#include "MainPlayerController.h"
#include "../view/HeadWear.h"
#include "../view/Shield.h"
#include "../view/Weapon.h"
#include <iostream>
#include <vector>

#define MANA_BAR_Y 58
#define HEALTH_BAR_Y 109
#define EXP_BAR_Y 45
#define GOLD_Y 10
#define GOLD_X 105
#define LEVEL_X 50
#define LEVEL_Y 24

MainPlayerController::MainPlayerController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void MainPlayerController::init(){
  MainPlayerData data = model.getMainPlayerData();

  TTF_Font* font = manager.getFont("arial");
  LTexture* healthText = manager.getTexture("healthText");
  LTexture* manaText = manager.getTexture("manaText");
  LTexture* goldText = manager.getTexture("goldText");
  LTexture* levelText = manager.getTexture("levelText");
  LTexture* expText = manager.getTexture("expText");
  
  playerView.init(manager.getTexture("clothes"));
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

  checkRace(data.rootd.prace);
  checkHealth(data.points.currentHP);
  checkEquipment(data.equipment);
}

void MainPlayerController::handleEvent(const SDL_Event &e,
  int cameraX, int cameraY) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      model.attack(
        e.button.x + cameraX - MAIN_SCREEN_BASE_MAP_X,
        e.button.y + cameraY - MAIN_SCREEN_BASE_MAP_Y);
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

std::vector<Entity*> MainPlayerController::getExp() {
  std::vector<Entity*> v;
  v.push_back(&level);
  v.push_back(&expBar);
  return v;
}

void MainPlayerController::checkRace(PlayerRace race) {
  if (playerView.ghostState()) return;

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

void MainPlayerController::checkEquipment(EquipmentData equipment){
  switch (equipment.body){
    case TUNIC:
      playerView.setBodyWear(manager.getTexture("blue-tunic"));
    break;
    case PLATE_ARMOR:
      playerView.setBodyWear(manager.getTexture("plate-armor"));
    break;
    case LEATHER_ARMOR:
      playerView.setBodyWear(manager.getTexture("leather-armor"));
    break;
    default:
      playerView.setBodyWear(manager.getTexture("clothes"));
    break;
  }

  switch (equipment.head){
    case HELMET:
      playerView.setHeadWear(HeadWear(manager.getTexture("helmet"), 
        3, -9, 0, -10));
    break;
    case HAT:
      playerView.setHeadWear(HeadWear(manager.getTexture("hat"), 
        3, -25, 0, -25));
    break;
    case HOOD:
      playerView.setHeadWear(HeadWear(manager.getTexture("hood"), 
        2, -10, -1, -10));
    break;
    default:
      playerView.setHeadWear(HeadWear(nullptr, 0, 0, 0, 0));
    break;
  }
  
  switch (equipment.leftHand){
    case TURTLE_SHIELD:
      playerView.setShield(Shield(manager.getTexture("turtle-shield"), 
        12, 14, 13, 18, 2, 60, 5, 17, 31, 104, 20, 16));
    break;
    case IRON_SHIELD:
      playerView.setShield(Shield(manager.getTexture("iron-shield"), 
        6, 10, 17, 24, 1, 60, 13, 16, 25, 104, 24, 18));
    break;
    default:
      playerView.setShield(Shield(nullptr, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    break;
  }

  switch (equipment.rightHand){
    case SIMPLE_BOW:
      playerView.setWeapon(Weapon(manager.getTexture("simple-bow"), 
        2, 6, 10, 20, 15, 56, 10, 14, 0, 141, 15, 15, 13, 5, 15, 10, 0, 5));
    break;
    case SWORD:
      playerView.setWeapon(Weapon(manager.getTexture("sword"), 
        34, 18, 17, 15, 44, 67, 4, 12, 9, 158, 13, 20, 17, 13, 20, 15, 2, 15));
    break;
    default:
      playerView.setWeapon(Weapon(nullptr, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    break;
  }
}

void MainPlayerController::checkHealth(int health) {
  if (health <= 0 && !playerView.ghostState()){
    playerView.setGhostAnimation(manager.getTexture("ghost"));
  }

  if (health > 0 && playerView.ghostState()){
    playerView.setPlayerAnimation(manager.getTexture("clothes"));
  }
}

MainPlayerController::~MainPlayerController() {}
