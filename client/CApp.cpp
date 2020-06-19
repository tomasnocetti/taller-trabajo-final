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
      // loginController.handleEvent(e);
      break;
    case GameMode::CREATE:
      break;
    case GameMode::RUN:
      playerController.handleEvent(e, 
        mapViewport.getCameraX(), mapViewport.getCameraY());
      break;
  }
}

void CApp::OnLoop() {
  //SDL_Delay(1000/60);
  playerController.update();
  enemyController.update();
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
      lifeViewport.paint(playerController.getBars());
      break;
  }
  window.render();
}

void CApp::OnInit() {
  LoadAssets();

  model.init();

  loginController.init();
  globalController.init();
  mapController.init();
  playerController.init();
  enemyController.init();

  mapViewport.init();
  MapData data = model.getMapData();
  mapViewport.setMaxCameraDimensions(data);
  lifeViewport.init();
}

void CApp::OnCleanup() {}

void CApp::LoadAssets() {
  manager.addFont("main", FONT_PATH, 12);
  manager.addTexture("main-screen-path", MAIN_SCREEN_PATH);
  manager.addTexture("login-screen-path", LOGIN_SCREEN_PATH);
  manager.addTexture("gold", "client/assets/health.png");
  manager.addTexture("clothes", "client/assets/clothes.png");
  manager.addTexture("blue-tunic", "client/assets/blue_tunic.png");
  manager.addTexture("plate-armor", "client/assets/plate_armor.png");
  manager.addTexture("leather-armor", "client/assets/leather_armor.png");
  manager.addTexture("health", "client/assets/health.png");
  manager.addTexture("mana", "client/assets/mana.png");
  manager.addTexture("dwarf-head", "client/assets/dwarf.png");
  manager.addTexture("elf-head", "client/assets/elf.png");
  manager.addTexture("human-head", "client/assets/human.png");
  manager.addTexture("skeleton-view", "client/assets/skeletonView.png");
  manager.addTexture("goblin-view", "client/assets/goblinView.png");
  manager.addTexture("spider-view", "client/assets/spiderView.png");
}

CApp::~CApp() {}
