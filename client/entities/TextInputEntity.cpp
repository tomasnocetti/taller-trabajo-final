#include "TextInputEntity.h"

#include <string>

#define CURSOR_ANIM_LAPSE 700

TextInputEntity::TextInputEntity(
  LTexture* texture,
  TTF_Font* font,
  int xpos,
  int ypos,
  int maxWidth,
  int maxHeight) :
  texture(texture),
  font(font),
  xpos(xpos),
  ypos(ypos),
  maxWidth(maxWidth),
  maxHeight(maxHeight) {}

void TextInputEntity::paint(double wScale, double hScale) {
  SDL_Color textColor = { 255, 255, 255, 0xFF };

  std::string showInput = input;
  int currentTime = SDL_GetTicks();
  if ((currentTime - lastRenderTime) >= CURSOR_ANIM_LAPSE && inside) {
    showInput += "|";
    if ((currentTime - lastRenderTime) >= CURSOR_ANIM_LAPSE * 2) {
      lastRenderTime = currentTime;
    }
  }
  if (showInput.length() <= 0) return;

  texture->loadFromRenderedText(
    font,
    showInput,
    textColor);

  int w, h;
	texture->queryTexture(w, h);
	SDL_Rect destRect = {xpos, ypos, w, h};

  texture->paint(destRect, wScale, hScale);
}

void TextInputEntity::handleClick(int xCoord, int yCoord) {
  SDL_Rect src = { this->xpos, this->ypos, maxWidth, maxHeight };
  //Check if mouse is in button
  inside = inRect(src, xCoord, yCoord);

  if (inside) {
    activateInput("");
  } else {
    SDL_StopTextInput();
  }
}

void TextInputEntity::handleInput(const SDL_Event& e) {
  switch (e.type) {
    case SDL_TEXTINPUT:
      if (!inside) return;
      input += e.text.text;

      break;
    case SDL_KEYDOWN:
      if (e.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0) {
        //lop off character
        input.pop_back();
      } else if (
        e.key.keysym.sym == SDLK_c
        && SDL_GetModState() & KMOD_CTRL ) {
        SDL_SetClipboardText(input.c_str());
      } else if (
        e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
        input = SDL_GetClipboardText();
      }
      break;
    default:
      break;
  }
}

void TextInputEntity::clearInput() {
  inside = false;
  SDL_StopTextInput();
  input.clear();
}

void TextInputEntity::activateInput(const std::string& c) {
  inside = true;
  SDL_StartTextInput();
  lastRenderTime = SDL_GetTicks();
  input += c;
}

std::string TextInputEntity::getInput() {
  return input;
}
