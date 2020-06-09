#ifndef _CAPP_H_
#define _CAPP_H_

#include <string>
#include <iostream>
#include "sdl/SdlWindow.h"
#include "viewports/Map.h"
#include "viewports/Global.h"
#include "controllers/MapController.h"

//Screen dimension constants
#define GAME_TITLE "Argentum"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class CApp {
  private:
    bool Running;
    // SDL_Surface* surface = NULL;
  public:
    CApp();
    CApp(const CApp&) = delete;
    CApp& operator=(const CApp&) = delete;
    ~CApp();
    void OnExecute();
  private:
    SdlWindow window;
    Global globalViewport;
    Map mapViewport;
    MapController mapController;
    void OnInit();
    void OnEvent(const SDL_Event& Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif
