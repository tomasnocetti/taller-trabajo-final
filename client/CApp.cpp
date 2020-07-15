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
  createController(model, manager),
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

	const int FPS = 45;
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
  if (model.isAuthenticated()) {
    playerController.handleEvent(e);
    chatController.handleEvent(e);
  } else if (model.isInCreationMode()) {
    createController.handleEvent(e);
  } else {
    loginController.handleEvent(e);
  }
}

void CApp::OnLoop() {
  model.update();
   if (model.isAuthenticated()) {
    mapController.update();
    mapController.updateDrops();
    playerController.update();
    chatController.update();
    enemyController.update();
    inventoryController.update();
    globalController.update();
  }
}

void CApp::OnRender() {
  window.clear();
  if (model.isAuthenticated()) {
    globalViewport.paint(globalController.getEntities());
    mapViewport.paint(
      playerController.getCamera(),
      mapController.getFloor(),
      mapController.getBackground(),
      mapController.getDrops(),
      playerController.getEntity(),
      enemyController.getNPCs(),
      enemyController.getOtherPlayers(), 
      mapController.getForeground());
    lifeViewport.paint(playerController.getBars());
    expViewport.paint(playerController.getExp());
    inventoryViewport.paint(inventoryController.getItems());
    chatViewport.paint(chatController.getEntities());
  } else if (model.isInCreationMode()) {
    globalViewport.paint(createController.getEntities());
  } else {
    globalViewport.paint(loginController.getEntities());
  }

  window.render();
}

void CApp::OnInit() {
  LoadAssets();

  model.init();

  loginController.init();
  createController.init();
  chatController.init();
  globalController.init();
  playerController.init();
}

void CApp::OnCleanup() {}

void CApp::LoadAssets() {
  manager.addFont("main", "/var/argentum/assets/fonts/ringm.ttf", 12);
  manager.addFont("arial", "/var/argentum/assets/fonts/arial.ttf", 12);
  manager.addTexture("main-screen-path", 
    "/var/argentum/assets/main-screens/game-screen.jpg");
  manager.addTexture("login-screen-path", 
    "/var/argentum/assets/main-screens/login-screen.jpg");
  manager.addTexture("create-screen-path", 
    "/var/argentum/assets/main-screens/create-screen.jpg");
  manager.addTextTexture("user-input");
  manager.addTextTexture("password-input");
  manager.addTexture("login-button", 
    "/var/argentum/assets/buttons/button-login-hover.png");
  manager.addTexture("login-button-active", 
    "/var/argentum/assets/buttons/button-login-active.png");
  manager.addTexture("create-button", 
    "/var/argentum/assets/buttons/button-create-pj-hover.png");
  manager.addTexture("create-button-active", 
    "/var/argentum/assets/buttons/button-create-pj-active.png");
  manager.addTexture("select-create", 
    "/var/argentum/assets/buttons/select-create.png");
  manager.addTexture("scroll-button",
    "/var/argentum/assets/buttons/scroll-button.png");
  manager.addTexture("scroll-button-active",
    "/var/argentum/assets/buttons/scroll-button-active.png");
    manager.addTexture("scroll-button-down",
    "/var/argentum/assets/buttons/button-scroll-down.png");
  manager.addTexture("scroll-button-down-active",
    "/var/argentum/assets/buttons/button-scroll-down-active.png");
  manager.addTextTexture("healthText");
  manager.addTextTexture("manaText");
  manager.addTextTexture("goldText");
  manager.addTextTexture("levelText");
  manager.addTextTexture("expText");
  manager.addTexture("clothes", "/var/argentum/assets/clothes.png");
  manager.addTexture("blue-tunic", "/var/argentum/assets/blue_tunic.png");
  manager.addTexture("plate-armor", "/var/argentum/assets/plate_armor.png");
  manager.addTexture("leather-armor", 
    "/var/argentum/assets/leather_armor.png");
  manager.addTexture("ghost", "/var/argentum/assets/ghost.png");
  manager.addTexture("health", "/var/argentum/assets/health.png");
  manager.addTexture("mana", "/var/argentum/assets/mana.png");
  manager.addTexture("exp", "/var/argentum/assets/exp.png");
  manager.addTexture("dwarf-head", "/var/argentum/assets/dwarf.png");
  manager.addTexture("elf-head", "/var/argentum/assets/elf.png");
  manager.addTexture("human-head", "/var/argentum/assets/human.png");
  manager.addTexture("gnome-head", "/var/argentum/assets/gnome.png");
  manager.addTexture("skeleton-view", "/var/argentum/assets/skeletonView.png");
  manager.addTexture("goblin-view", "/var/argentum/assets/goblinView.png");
  manager.addTexture("spider-view", "/var/argentum/assets/spiderView.png");
  manager.addTexture("zombie-view", "/var/argentum/assets/zombieView.png");
  manager.addTexture("helmet", "/var/argentum/assets/iron_helm.png");
  manager.addTexture("hat", "/var/argentum/assets/hat.png");
  manager.addTexture("hood", "/var/argentum/assets/hood.png");
  manager.addTexture("turtle-shield", 
    "/var/argentum/assets/turtle_shield.png");
  manager.addTexture("iron-shield", 
    "/var/argentum/assets/iron_shield.png");
  manager.addTexture("simple-bow", "/var/argentum/assets/simpleBow.png");
  manager.addTexture("ash-stick", "/var/argentum/assets/ash_stick.png");
  manager.addTexture("gnarled-staff", 
    "/var/argentum/assets/gnarled_staff.png");
  manager.addTexture("socketed-staff", 
    "/var/argentum/assets/socketed_staff.png");
  manager.addTexture("axe", "/var/argentum/assets/axe.png");
  manager.addTexture("elfic-flute", "/var/argentum/assets/elfic_flute.png");
  manager.addTexture("sword", "/var/argentum/assets/sword.png");
  manager.addTexture("mace", "/var/argentum/assets/mace.png");
  manager.addTextTexture("invText_1");
  manager.addTextTexture("invText_2");
  manager.addTextTexture("invText_3");
  manager.addTextTexture("invText_4");
  manager.addTextTexture("invText_5");
  manager.addTextTexture("invText_6");
  manager.addTextTexture("invText_7");
  manager.addTextTexture("invText_8");
  manager.addTextTexture("invText_9");
  manager.addTexture("check", "/var/argentum/assets/check.png");
  manager.addTexture("item_1", "/var/argentum/assets/bow_inv.png");
  manager.addTexture("item_2", "/var/argentum/assets/sword_inv.png");
  manager.addTexture("item_3", "/var/argentum/assets/iron_helm_inv.png");
  manager.addTexture("item_4", "/var/argentum/assets/iron_shield_inv.png");
  manager.addTexture("item_5", "/var/argentum/assets/blue_tunic_inv.png");
  manager.addTexture("item_6", "/var/argentum/assets/ash_stick_inv.png");
  manager.addTexture("item_7", "/var/argentum/assets/hat_inv.png");
  manager.addTexture("item_8", "/var/argentum/assets/hood_inv.png");
  manager.addTexture("item_9", "/var/argentum/assets/leather_armor_inv.png");
  manager.addTexture("item_10", "/var/argentum/assets/plate_armor_inv.png");
  manager.addTexture("item_11", "/var/argentum/assets/turtle_shield_inv.png");
  manager.addTexture("item_12", "/var/argentum/assets/gnarled_staff_inv.png");
  manager.addTexture("item_13", "/var/argentum/assets/elfic_flute_inv.png");
  manager.addTexture("item_14", "/var/argentum/assets/socketed_staff_inv.png");
  manager.addTexture("item_15", "/var/argentum/assets/axe_inv.png");
  manager.addTexture("item_16", "/var/argentum/assets/mace_inv.png");
  manager.addTexture("item_17", "/var/argentum/assets/composite_bow_inv.png");
  manager.addTexture("item_18", "/var/argentum/assets/mana_potion.png");
  manager.addTexture("item_19", "/var/argentum/assets/health_potion.png");
  manager.addTexture("item_5000", "/var/argentum/assets/gold.png");

  manager.addMusic("main-music", "/var/argentum/assets/music/main_music.mp3");
  manager.addSFX("h2h-sound", "/var/argentum/assets/sounds/h2h_sound.wav");
  manager.addSFX("bow-sound", "/var/argentum/assets/sounds/bow_sound.wav");
  manager.addSFX("magic-sound", "/var/argentum/assets/sounds/magic_sound.wav");
}

CApp::~CApp() {}
