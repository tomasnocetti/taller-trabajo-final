#include "CApp.h"
#include <string>

CApp::CApp(std::string& host, std::string& port) :
  model(host, port),
  window(SCREEN_WIDTH, SCREEN_HEIGHT),
  manager(window),
  globalViewport(window),
  mapViewport(window),
  lifeViewport(window),
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
  playerController.handleEvent(e);
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
  window.clear();
  globalViewport.paint(globalController.getEntities());
  mapViewport.paint(mapController.getEntities(),
    playerController.getEntity(),
    enemyController.getEntity());
  lifeViewport.paint();
  window.render();
}

void CApp::OnInit() {
  model.init();
  mapViewport.init();
  lifeViewport.init();
  globalController.init();
  mapController.init();
  playerController.init();
  enemyController.init();
}

void CApp::OnCleanup() {}

CApp::~CApp() {}
