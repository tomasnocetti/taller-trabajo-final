#ifndef _CAPP_H_
#define _CAPP_H_

#include <string>
#include "sdl/SdlWindow.h"
#include "sdl/SdlAssetsManager.h"
#include "model/ServerProxy.h"
#include "viewports/Viewports.h"
#include "controllers/Controllers.h"

//Screen dimension constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define ASSETS_PATH "/var/argentum/assets"

class CApp {
  public:
    CApp(std::string& host, std::string& port);
    CApp(const CApp&) = delete;
    CApp& operator=(const CApp&) = delete;
    ~CApp();
    void OnExecute();

  private:
    bool Running;
    ServerProxy model;
    SdlWindow window;
    SdlAssetsManager manager;
    Global globalViewport;
    Map mapViewport;
    LifeViewport lifeViewport;
    ExpViewport expViewport;
    InventoryViewport inventoryViewport;
    ChatViewport chatViewport;
    LoginController loginController;
    CreateController createController;
    ChatController chatController;
    GlobalController globalController;
    MapController mapController;
    MainPlayerController playerController;
    EnemyController enemyController;
    InventoryController inventoryController;
    void OnInit();
    void LoadAssets();
    void OnEvent(SDL_Event& Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif
