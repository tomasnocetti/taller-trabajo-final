#include "ButtonEntity.h"

#include <string>

ButtonEntity::ButtonEntity(
  LTexture* mainT,
  int xpos,
  int ypos,
  int w,
  int h,
  LTexture* activeT) :
  mainT(mainT),
  activeT(activeT),
  xpos(xpos),
  ypos(ypos),
  w(w),
  h(h) {}

void ButtonEntity::paint(double wScale, double hScale) {
  if (click && activeT != nullptr) {
    activeT->paint(xpos, ypos, wScale, hScale);
  } else if (inside && hoverT != nullptr) {
    hoverT->paint(xpos, ypos, wScale, hScale);
  } else if (mainT != nullptr) {
    mainT->paint(xpos, ypos, wScale, hScale);
  }
}

void ButtonEntity::handleClick(int xCoord, int yCoord) {
  SDL_Rect src = { this->xpos, this->ypos, w, h };
  click = inRect(src, xCoord, yCoord);
}

void ButtonEntity::handleClickClear() {
  click = false;
}

bool ButtonEntity::isActive() {
  return click;
}
