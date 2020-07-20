#include "CreateController.h"
#include <string>

CreateController::CreateController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void CreateController::init() {
  initElements();
  LTexture* baseScreen = manager.getTexture("create-screen-path");
  screens.emplace_back(new BackgroundEntity(baseScreen));
  screens.emplace_back(createButton);
  screens.emplace_back(userInputField);
  screens.emplace_back(passwordInputField);
  for (auto& it : activeClass){
    screens.push_back(it.second);
  }
  for (auto& it : activeRace){
    screens.emplace_back(it.second);
  }
}

void CreateController::initElements() {
  LTexture* userInput = manager.getTexture("user-input");
  LTexture* passInput = manager.getTexture("password-input");
  TTF_Font* font = manager.getFont("arial");

  userInputField = std::shared_ptr<TextInputEntity>(
    new TextInputEntity(userInput, font, 218, 109, 135, 40));
  passwordInputField = std::shared_ptr<TextInputEntity>(
    new TextInputEntity(passInput, font, 458, 109, 135, 40));
  createButton = std::unique_ptr<ButtonEntity>(new ButtonEntity(
      manager.getTexture("create-button"),
      BTN_POS_X,
      BTN_POS_Y,
      BTN_POS_W,
      BTN_POS_H,
      manager.getTexture("create-button-active")));

  activeClass.insert(classItem(
    PlayerClass::WARRIOR,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, C1X, C1Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));

  activeClass.insert(classItem(
    PlayerClass::CLERIC,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, C2X, C2Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));

  activeClass.insert(classItem(
    PlayerClass::MAGE,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, C3X, C3Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));

  activeClass.insert(classItem(
    PlayerClass::PALADIN,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, C4X, C4Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));


  activeRace.insert(raceItem(
    PlayerRace::HUMAN,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, R1X, R1Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));

  activeRace.insert(raceItem(
    PlayerRace::ELF,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, R2X, R2Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));

  activeRace.insert(raceItem(
    PlayerRace::DWARF,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, R3X, R3Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));

  activeRace.insert(raceItem(
    PlayerRace::GNOME,
    std::unique_ptr<ButtonEntity>(new ButtonEntity(
      nullptr, R4X, R4Y, BTN_WIDTH_S, BTN_HEIGHT_S,
      manager.getTexture("select-create")))));
}

void CreateController::handleEvent(const SDL_Event &e) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      createButton->handleClick(e.button.x, e.button.y);
      passwordInputField->handleClick(
        e.button.x, e.button.y);
      userInputField->handleClick(
        e.button.x, e.button.y);
      SDL_Rect classSelection =
        {C1X, C1Y, SEL_WIDTH, SEL_HEIGHT};
      if (inRect(classSelection, e.button.x, e.button.y)) {
        for (auto& it : activeClass){
          it.second->handleClickClear();
          it.second->handleClick(e.button.x, e.button.y);
        }
      }
      SDL_Rect raceSelection = {R1X, R1Y, SEL_WIDTH, SEL_HEIGHT};
      if (inRect(raceSelection, e.button.x, e.button.y)) {
        for (auto& it : activeRace){
          it.second->handleClickClear();
          it.second->handleClick(e.button.x, e.button.y);
        }
      }
    }
  }
  if (e.type == SDL_MOUSEBUTTONUP && 
    e.button.button == SDL_BUTTON_LEFT){
    if (createButton->isActive()) {
      create();
      createButton->handleClickClear();
    }
  }
  passwordInputField->handleInput(e);
  userInputField->handleInput(e);
}

void CreateController::create() {
  std::string nick = userInputField->getInput();
  std::string passw = passwordInputField->getInput();
  std::string race = "";
  std::string classT = "";

  for (auto& it : activeRace){
    if (!it.second->isActive()) continue;
    race += static_cast<char>(it.first);
  }

  for (auto& it : activeClass){
    if (!it.second->isActive()) continue;
    classT += static_cast<char>(it.first);
  }

  if (nick.empty() || passw.empty() ||
    race.empty() || classT.empty()) {
      return;
    }

  model.createPlayer(nick, passw, race, classT);
}

EntityList& CreateController::getEntities() {
  return screens;
}
