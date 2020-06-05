#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "LTexture.h"

//Screen dimension constants
#define GAME_TITLE "Argentum"
#define MAIN_SCREEN_PATH "assets/main-screen.jpg"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


class CApp {
  private:
    bool Running;
    // SDL_Surface* surface = NULL;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
  public:
    CApp();
    void OnExecute();
  private:
    void InitMainIterface();
    void OnInit();
    void OnEvent(const SDL_Event& Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif