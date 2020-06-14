#ifndef _CAPP_H_
#define _CAPP_H_

#include <string>
#include "sdl/SdlWindow.h"
#include "sdl/SdlAssetsManager.h"
#include "model/ClientProxy.h"
#include "viewports/Viewports.h"
#include "controllers/Controllers.h"

//Screen dimension constants
#define GAME_TITLE "Argentum" 

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class CApp {
  private:
    bool Running;
    // SDL_Surface* surface = NULL;
  public:
    CApp(std::string& host, std::string& port);
    CApp(const CApp&) = delete;
    CApp& operator=(const CApp&) = delete;
    ~CApp();
    void OnExecute();
    
  private:
    ClientProxy model;
    SdlWindow window;
    SdlAssetsManager manager;
    Global globalViewport;
    Map mapViewport;
    LifeViewport lifeViewport;
    GlobalController globalController;
    MapController mapController;
    MainPlayerController playerController;
    EnemyController enemyController;
    void OnInit();
    void OnEvent(const SDL_Event& Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif
