#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "SdlException.h"
#include "SdlWindow.h"
#include <iostream>

SdlWindow::SdlWindow(int width, int height) :
  baseWidth(width),
  baseHeight(height),
  width(width),
  height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
      throw SdlException("Error en la inicialización", SDL_GetError());
    }

    window = SDL_CreateWindow(
      "GAME_TITLE",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width,
      height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
      throw SdlException("Error en la inicialización Window", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
      throw SdlException("Error en la inicialización Renderer", SDL_GetError());
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Initialize JPG loading
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
      throw SdlException("Error en la inicialización IMG", IMG_GetError());
    }
    if (TTF_Init() == -1) {
      throw SdlException("Error en la inicialización SDL_TTF", TTF_GetError());
    }
}

SdlWindow::~SdlWindow() {
  std::cout << "Destruyendo" << std::endl;

  if (this->renderer) {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
  }

  if (this->window) {
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
  }
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void SdlWindow::handleEvent(const SDL_Event& e) {
	//Window event occured
	if ( e.type != SDL_WINDOWEVENT ) return;

  switch ( e.window.event ) {
    //Get new dimensions and repaint on window size change
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      width = e.window.data1;
      height = e.window.data2;
      render();
      break;

    //Repaint on exposure
    case SDL_WINDOWEVENT_EXPOSED:
      render();
      break;
  }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
  SDL_SetRenderDrawColor(this->renderer,
                          r, g, b, alpha);
  SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
  this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::render() {
  SDL_RenderPresent(this->renderer);
}

void SdlWindow::clear() {
  SDL_RenderClear(this->renderer);
}

double SdlWindow::getScaleWidthFactor() const {
  return static_cast<double> (width) / static_cast<double> (baseWidth);
}

double SdlWindow::getScaleHeightFactor() const {
  return static_cast<double> (height) / static_cast<double> (baseHeight);
}

SDL_Renderer* SdlWindow::getRenderer() const {
  return this->renderer;
}

LTexture* SdlWindow::createTexture() const {
  return new LTexture(renderer);
}
