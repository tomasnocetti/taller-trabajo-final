#include "LoginController.h"

#include <string>
#define LOGIN_SCREEN_PATH "client/assets/main-screens/login-screen.jpg"

LoginController::LoginController(
  ServerProxy& model,
  SdlAssetsManager& manager) :
  model(model),
  manager(manager) {}

void LoginController::init() {
  LTexture* baseScreen = manager.getTexture("login-screen-path");
  LTexture* userInput = manager.getTexture("user-input");
  LTexture* passInput = manager.getTexture("password-input");
  TTF_Font* font = manager.getFont("arial");

  screens.emplace_back(new BackgroundEntity(baseScreen));

  userInputField = std::shared_ptr<TextInputEntity>(
    new TextInputEntity(userInput, font, 345, 262, 135, 40));
  passwordInputField = std::shared_ptr<TextInputEntity>(
    new TextInputEntity(passInput, font, 345, 335, 135, 40));
  loginButton = std::unique_ptr<ButtonEntity>(new ButtonEntity(
      manager.getTexture("login-button"),
      327,
      380,
      165,
      49,
      manager.getTexture("login-button-active")));
  createButton = std::unique_ptr<ButtonEntity>(new ButtonEntity(
      manager.getTexture("create-button"),
      600,
      500,
      165,
      49,
      manager.getTexture("create-button-active")));
  screens.emplace_back(loginButton);
  screens.emplace_back(createButton);
  screens.emplace_back(userInputField);
  screens.emplace_back(passwordInputField);
}

void LoginController::handleEvent(const SDL_Event &e) {
  if (e.type == SDL_MOUSEMOTION) return;

  if (e.type == SDL_MOUSEBUTTONDOWN){
    if (e.button.button == SDL_BUTTON_LEFT){
      loginButton->handleClick(e.button.x, e.button.y);
      createButton->handleClick(e.button.x, e.button.y);
      passwordInputField->handleClick(
        e.button.x, e.button.y);
      userInputField->handleClick(
        e.button.x, e.button.y);
    }
  }
  passwordInputField->handleInput(e);
  userInputField->handleInput(e);

  if (e.type == SDL_MOUSEBUTTONUP && 
    e.button.button == SDL_BUTTON_LEFT){
    if (createButton->isActive()) {
      model.setInCreationMode();
      createButton->handleClickClear();
    }
    if (loginButton->isActive()) {
      login();
      loginButton->handleClickClear();
    }
  }
}

void LoginController::login() {
  std::string nick = userInputField->getInput();
  std::string password = passwordInputField->getInput();

  if (nick.empty() || password.empty()) return;

  model.authentificate(nick, password);
}

EntityList& LoginController::getEntities() {
  return screens;
}
