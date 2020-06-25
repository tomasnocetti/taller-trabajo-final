#include "MainPlayerController.h"
#include "../view/HeadWear.h"
#include <iostream>
#include <vector>

#define MANA_BAR_Y 58
#define HEALTH_BAR_Y 109
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
  
  playerView.init(manager.getTexture("clothes"));
  checkRace(data.rootd.prace);
  healthBar.init(manager.getTexture("health"), HEALTH_BAR_Y,
    healthText, font);
  manaBar.init(manager.getTexture("mana"), MANA_BAR_Y, manaText, font);
  gold.init(GOLD_X, GOLD_Y, goldText, font);
  level.init(LEVEL_X, LEVEL_Y, levelText, font);
}

void MainPlayerController::update() {
  MainPlayerData data = model.getMainPlayerData();
  playerView.move(data.position.x, data.position.y);

  healthBar.update(data.points.currentHP, data.points.totalHP);
  manaBar.update(data.points.currentMP, data.points.totalMP);
  gold.update(std::to_string(data.gold));
  level.update(data.nick + " - nivel: " + 
    std::to_string(data.level));

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

void MainPlayerController::checkEquipment(EquipmentData equipment){
  switch(equipment.body){
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

  switch(equipment.head){
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
  
  /*if(equipment.rightHand != equipped.rightHand){
    switch(equipment.head){
      case HELMET:
        {
        playerView.setShield(shield);
        }
      break;
      case HAT:
        {
        std::shared_ptr<MagicHat> headWear(
          new MagicHat(manager.getTexture("hat")));
        playerView.setHeadWear(headWear);
        }
      break;
      default:
      break;
    }
    equipped.rightHand = equipment.rightHand;
  }*/
}

MainPlayerController::~MainPlayerController() {}
