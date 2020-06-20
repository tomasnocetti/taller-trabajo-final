#include "TextInputEntity.h"

#include <string>

TextInputEntity::TextInputEntity(
  LTexture* texture,
  TTF_Font* font,
  int xpos,
  int ypos) :
  texture(texture),
  font(font),
  xpos(xpos),
  ypos(ypos) {}

void TextInputEntity::paint(double wScale, double hScale) {
  SDL_Color textColor = { 255, 255, 255, 0xFF };
  texture->loadFromRenderedText(
    font,
    std::string("Tomi123"),
    textColor);

  texture->paint(xpos, ypos, wScale, hScale);
}
