#include "ButtonEntity.h"

#include <string>

ButtonEntity::ButtonEntity(
  LTexture* mainT,
  int xpos,
  int ypos,
  LTexture* activeT,
  LTexture* hoverT) :
  mainT(mainT),
  activeT(activeT),
  hoverT(hoverT),
  xpos(xpos),
  ypos(ypos) {}

void ButtonEntity::paint(double wScale, double hScale) {

  lWScale = wScale;
  lHScale = hScale;

  if (click && activeT != nullptr) {
    activeT->paint(xpos, ypos, wScale, hScale);
  } else if (inside && hoverT != nullptr) {
    hoverT->paint(xpos, ypos, wScale, hScale);
  } else if (mainT != nullptr) {
    mainT->paint(xpos, ypos, wScale, hScale);
  }
}

void ButtonEntity::handleEvent(const SDL_Event &e) {

    SDL_Rect src = { this->xpos, this->ypos, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect dest = sdlScaleRect(src, lWScale, lHScale);
    int x, y;

    switch (e.type) {
      case SDL_MOUSEMOTION:

        //Get mouse position
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        inside = inRect(dest, x, y);
        break;
      case SDL_MOUSEBUTTONDOWN:

        SDL_GetMouseState( &x, &y );

        click = inRect(dest, x, y);
        break;
      case SDL_MOUSEBUTTONUP:
        click = false;
        break;
      default:
        break;
    }
};