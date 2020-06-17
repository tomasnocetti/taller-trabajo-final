#include "TextInputEntity.h"

#include <string>


TextInputEntity::TextInputEntity(
  LTexture* texture,
  TTF_Font* font,
  int size,
  int xpos,
  int ypos) :
  texture(texture),
  font(font),
  size(size),
  xpos(xpos),
  ypos(ypos) {}

void TextInputEntity::paint(double wScale, double hScale) {
  SDL_Color textColor = { 255, 255, 255, 0xFF };

  lWScale = wScale;
  lHScale = hScale;
  if (input.length() <= 0) return;

  texture->loadFromRenderedText(
    font,
    input,
    textColor);

  texture->paint(xpos, ypos, wScale, hScale);
}

void TextInputEntity::handleEvent(const SDL_Event &e) {

    SDL_Rect src = { this->xpos, this->ypos, BUTTON_WIDTH, BUTTON_HEIGHT };
    SDL_Rect dest = sdlScaleRect(src, lWScale, lHScale);

    switch (e.type) {
      case SDL_MOUSEBUTTONDOWN:

        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );


        //Check if mouse is in button
        inside = true;

        //Mouse is left of the button
        if( x < xpos ) {
          inside = false;
        }
        //Mouse is right of the button
        else if( x > dest.x + dest.w )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < dest.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > dest.y + dest.h )
        {
            inside = false;
        }
        if(inside) {
          SDL_StartTextInput();
        } else {
          SDL_StopTextInput();
        }
        break;
      case SDL_TEXTINPUT:
        if (!inside) return;
        input += e.text.text;

        break;
      case SDL_KEYDOWN:
        if( e.key.keysym.sym == SDLK_BACKSPACE && input.length() > 0 ) {
          //lop off character
          input.pop_back();
        } else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL ) {
          SDL_SetClipboardText( input.c_str() );
        } else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL ) {
          input = SDL_GetClipboardText();
        }
        break;
      default:
        break;
    }

};