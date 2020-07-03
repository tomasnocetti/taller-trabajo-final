#include "CApp.h"
#include <string>

CApp::CApp(std::string& host, std::string& port) :
  model(host, port),
  window(SCREEN_WIDTH, SCREEN_HEIGHT),
  manager(window),
  globalViewport(window),
  mapViewport(window),
  lifeViewport(window),
  expViewport(window),
  inventoryViewport(window),
  chatViewport(window),
  loginController(model, manager),
  chatController(model, manager),
  globalController(model, manager),
  mapController(model, manager),
  playerController(model, manager),
  enemyController(model, manager),
  inventoryController(model, manager) {
  Running = true;
}

void CApp::OnExecute() {
  OnInit();
  SDL_Event Event;

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

  while (Running) {
    frameStart = SDL_GetTicks();
    while (SDL_PollEvent(&Event)){
      OnEvent(Event);
    }

    OnLoop();
    OnRender();

    frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}
  }

  OnCleanup();
}

void CApp::OnEvent(SDL_Event& e) {
  if (e.type == SDL_QUIT) {
    model.close();
    Running = false;
  }

  window.handleEvent(e);
  switch (mode) {
    case GameMode::LOGIN:
      loginController.handleEvent(e);
      break;
    case GameMode::CREATE:
      break;
    case GameMode::RUN:
      playerController.handleEvent(e);
      chatController.handleEvent(e);
      break;
  }
}

void CApp::OnLoop() {
  model.update();
  mapController.update();
  mapController.updateDrops();
  playerController.update();
  chatController.update();
  enemyController.update();
  inventoryController.update();
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
      mapViewport.paint(
        playerController.getCamera(),
        mapController.getEntities(),
        mapController.getDrops(),
        playerController.getEntity(),
        enemyController.getNPCs(),
        enemyController.getOtherPlayers());
      lifeViewport.paint(playerController.getBars());
      expViewport.paint(playerController.getExp());
      inventoryViewport.paint(inventoryController.getItems());
      chatViewport.paint(chatController.getEntities());
      break;
  }
  window.render();
}

void CApp::OnInit() {
  LoadAssets();

  model.init();

  loginController.init();
  chatController.init();
  globalController.init();
  playerController.init();
}

void CApp::OnCleanup() {}

void CApp::LoadAssets() {
  manager.addFont("main", FONT_PATH, 12);
  manager.addFont("arial", ARIAL_PATH, 12);
  manager.addTexture("main-screen-path", MAIN_SCREEN_PATH);
  manager.addTexture("login-screen-path", LOGIN_SCREEN_PATH);
  manager.addTextTexture("user-input");
  manager.addTexture("scroll-button",
    "client/assets/buttons/scroll-button.png");
  manager.addTexture("scroll-button-active",
    "client/assets/buttons/scroll-button-active.png");
    manager.addTexture("scroll-button-down",
    "client/assets/buttons/button-scroll-down.png");
  manager.addTexture("scroll-button-down-active",
    "client/assets/buttons/button-scroll-down-active.png");
  manager.addTextTexture("healthText");
  manager.addTextTexture("manaText");
  manager.addTextTexture("goldText");
  manager.addTextTexture("levelText");
  manager.addTextTexture("expText");
  manager.addTexture("clothes", "client/assets/clothes.png");
  manager.addTexture("blue-tunic", "client/assets/blue_tunic.png");
  manager.addTexture("plate-armor", "client/assets/plate_armor.png");
  manager.addTexture("leather-armor", "client/assets/leather_armor.png");
  manager.addTexture("ghost", "client/assets/ghost.png");
  manager.addTexture("health", "client/assets/health.png");
  manager.addTexture("mana", "client/assets/mana.png");
  manager.addTexture("exp", "client/assets/exp.png");
  manager.addTexture("dwarf-head", "client/assets/dwarf.png");
  manager.addTexture("elf-head", "client/assets/elf.png");
  manager.addTexture("human-head", "client/assets/human.png");
  manager.addTexture("gnome-head", "client/assets/gnome.png");
  manager.addTexture("skeleton-view", "client/assets/skeletonView.png");
  manager.addTexture("goblin-view", "client/assets/goblinView.png");
  manager.addTexture("spider-view", "client/assets/spiderView.png");
  manager.addTexture("zombie-view", "client/assets/zombieView.png");
  manager.addTexture("helmet", "client/assets/iron_helm.png");
  manager.addTexture("hat", "client/assets/hat.png");
  manager.addTexture("hood", "client/assets/hood.png");
  manager.addTexture("turtle-shield", "client/assets/turtle_shield.png");
  manager.addTexture("iron-shield", "client/assets/iron_shield.png");
  manager.addTexture("simple-bow", "client/assets/simpleBow.png");
  manager.addTexture("ash-stick", "client/assets/ash_stick.png");
  manager.addTexture("gnarled-staff", "client/assets/gnarled_staff.png");
  manager.addTexture("elfic-flute", "client/assets/elfic_flute.png");
  manager.addTexture("sword", "client/assets/sword.png");
  manager.addTextTexture("invText_1");
  manager.addTextTexture("invText_2");
  manager.addTextTexture("invText_3");
  manager.addTextTexture("invText_4");
  manager.addTextTexture("invText_5");
  manager.addTextTexture("invText_6");
  manager.addTextTexture("invText_7");
  manager.addTextTexture("invText_8");
  manager.addTextTexture("invText_9");
  manager.addTexture("check", "client/assets/check.png");
  manager.addTexture("item_1", "client/assets/bow_inv.png");
  manager.addTexture("item_2", "client/assets/sword_inv.png");
  manager.addTexture("item_3", "client/assets/iron_helm_inv.png");
  manager.addTexture("item_4", "client/assets/iron_shield_inv.png");
  manager.addTexture("item_5", "client/assets/blue_tunic_inv.png");
  manager.addTexture("item_6", "client/assets/ash_stick_inv.png");
  manager.addTexture("item_7", "client/assets/hat_inv.png");
  manager.addTexture("item_8", "client/assets/hood_inv.png");
  manager.addTexture("item_9", "client/assets/leather_armor_inv.png");
  manager.addTexture("item_10", "client/assets/plate_armor_inv.png");
  manager.addTexture("item_11", "client/assets/turtle_shield_inv.png");
  manager.addTexture("item_12", "client/assets/gnarled_staff_inv.png");
  manager.addTexture("item_13", "client/assets/elfic_flute_inv.png");
  manager.addTexture("item_18", "client/assets/mana_potion.png");
  manager.addTexture("item_19", "client/assets/health_potion.png");
  manager.addTexture("item_5000", "client/assets/gold.png");
}

CApp::~CApp() {}
