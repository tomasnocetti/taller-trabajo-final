#include "CApp.h"
#include <string>

CApp::CApp(std::string& host, std::string& port) :
  model(host, port),
  window(SCREEN_WIDTH, SCREEN_HEIGHT),
  manager(window),
  globalViewport(window),
  mapViewport(window),
  lifeViewport(window),
  loginController(model, manager),
  globalController(model, manager),
  mapController(model, manager),
  playerController(model, manager),
  enemyController(model, manager) {
  Running = true;
}

void CApp::OnExecute() {
  OnInit();
  SDL_Event Event;

  while (Running) {
    while (SDL_PollEvent(&Event)){
      OnEvent(Event);
    }

    OnLoop();
    OnRender();
  }

  OnCleanup();
}

void CApp::OnEvent(const SDL_Event& e) {
  if (e.type == SDL_QUIT) {
    Running = false;
  }
  window.handleEvent(e);
  switch (mode) {
    case GameMode::LOGIN:
      break;
    case GameMode::CREATE:
      break;
    case GameMode::RUN:
      playerController.handleEvent(e);
      break;
  }
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
  window.clear();

  switch (mode) {
    case GameMode::LOGIN:
      globalViewport.paint(loginController.getEntities());
      break;
    case GameMode::CREATE:
      break;
    case GameMode::RUN:
      globalViewport.paint(globalController.getEntities());
      mapViewport.paint(mapController.getEntities(),
        playerController.getEntity(),
        enemyController.getEntity());
      lifeViewport.paint();
      break;
  }
  window.render();
}

void CApp::OnInit() {
  model.init();
  mapViewport.init();
  lifeViewport.init();
  loginController.init();
  globalController.init();
  mapController.init();
  playerController.init();
  enemyController.init();
}

void CApp::OnCleanup() {}

CApp::~CApp() {}
