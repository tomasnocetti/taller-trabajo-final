#include "CApp.h"
#include <string>

CApp::CApp(std::string& host, std::string& port) :
  model(host, port),
  window(SCREEN_WIDTH, SCREEN_HEIGHT),
  globalViewport(window),
  mapViewport(window),
  mapController(model),
  playerController(model) {
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
  globalViewport.paint();
  mapViewport.paint(mapController.getEntities(), 
    playerController.getEntity(), 
    enemyController.getEntity());
  window.render();
}

void CApp::OnInit() {
  mapViewport.init();
  mapController.init(window);
  playerController.init(window, (542 - 11) / 2, (413 - 154) / 2);
  std::vector<struct EnemyData> v;
  struct EnemyData data;
  data.x = 100;
  data.y = 100;
  data.type = 's';
  v.push_back(data);
  enemyController.init(window, v);
}

void CApp::OnCleanup() {}

CApp::~CApp() {}
