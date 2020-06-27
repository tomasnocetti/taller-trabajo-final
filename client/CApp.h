#ifndef _CAPP_H_
#define _CAPP_H_

#include <string>
#include "sdl/SdlWindow.h"
#include "sdl/SdlAssetsManager.h"
#include "model/ServerProxy.h"
#include "viewports/Viewports.h"
#include "controllers/Controllers.h"

//Screen dimension constants
#define GAME_TITLE "Argentum" 

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef enum {
  LOGIN,
  CREATE,
  RUN
} GameMode;

#define MAIN_SCREEN_PATH "client/assets/main-screens/game-screen.jpg"
#define LOGIN_SCREEN_PATH "client/assets/main-screens/login-screen.jpg"
#define FONT_PATH "client/assets/fonts/ringm.ttf"
#define ARIAL_PATH "client/assets/fonts/arial.ttf"

class CApp {
  public:
    CApp(std::string& host, std::string& port);
    CApp(const CApp&) = delete;
    CApp& operator=(const CApp&) = delete;
    ~CApp();
    void OnExecute();

  private:
    bool Running;
    GameMode mode = GameMode::RUN;
    ServerProxy model;
    SdlWindow window;
    SdlAssetsManager manager;
    Global globalViewport;
    Map mapViewport;
    LifeViewport lifeViewport;
    ExpViewport expViewport;
    LoginController loginController;
    GlobalController globalController;
    MapController mapController;
    MainPlayerController playerController;
    EnemyController enemyController;
    void OnInit();
    void LoadAssets();
    void OnEvent(SDL_Event& Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif
