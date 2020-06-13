#include "CApp.h"
#include <cmath>

CApp::CApp() :
  window(SCREEN_WIDTH, SCREEN_HEIGHT),
  globalViewport(window),
  mapViewport(window) {
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
  //mapViewport.handleEvent(e);
  playerController.handleEvent(e);
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
  window.clear();
  globalViewport.paint();
  mapViewport.paint(mapController.getEntities(), 
    playerController.getEntity());
  window.render();
}

void CApp::OnInit() {
  mapViewport.init();
  mapController.init(window);
  //playerController.init((542 - 11) / 2, (413 - 154) / 2);
  playerController.init(window.createTexture(), (542 - 11) / 2, (413 - 154) / 2);
}

void CApp::OnCleanup() {}

CApp::~CApp() {}
