#include "ChatArea.h"

#include <string>
#include "../../DataDefinitions.h"

ChatArea::ChatArea(
  SdlAssetsManager& manager,
  int xpos,
  int ypos,
  int maxWidth,
  int maxHeight,
  int paddingV,
  int lineHeight) :
  manager(manager),
  x(xpos),
  y(ypos),
  maxWidth(maxWidth),
  maxHeight(maxHeight),
  paddingV(paddingV),
  lineHeight(lineHeight) {
    manager.addTextTexture("area-line1");
    scrollup = std::unique_ptr<ButtonEntity>(new ButtonEntity(
      manager.getTexture("scroll-button"),
      maxWidth - SCROLL_BUTTON_S,
      0,
      SCROLL_BUTTON_S,
      SCROLL_BUTTON_S,
      manager.getTexture("scroll-button-active")));
    scrolldown = std::unique_ptr<ButtonEntity> (new ButtonEntity(
      manager.getTexture("scroll-button-down"),
      maxWidth - SCROLL_BUTTON_S,
      maxHeight - SCROLL_BUTTON_S,
      SCROLL_BUTTON_S,
      SCROLL_BUTTON_S,
      manager.getTexture("scroll-button-down-active")));
    currentIndex = -1;
  }

void ChatArea::update(ChatData& chat) {
  /** Logica para que si el currentIndex es el ultimo entonces
   * cada nuevo mensaje se actualiza el chat y lo ves. Pero si no es el caso
   * tenes que scrollear. **/
  if ((previousSize == 0 && currentIndex == 0) ||
    previousSize == (currentIndex + 1)) {
    currentIndex = chat.entries.size() - 1;
  }
  previousSize = chat.entries.size();
  inputs = chat.entries;
}

void ChatArea::handleClick(int xCoord, int yCoord) {
  scrollup->handleClick(xCoord, yCoord);
  scrolldown->handleClick(xCoord, yCoord);
}

void ChatArea::handleClickClear() {
  scrollup->handleClickClear();
  scrolldown->handleClickClear();
}

void ChatArea::paint(double wScale, double hScale) {
  int currentTime = SDL_GetTicks();
  if ((currentTime - lastRenderTime) >= SCROLL_LAPSE) {
    if (scrollup->isActive()
      && currentIndex > 0
      && (currentIndex + 1) * lineHeight > (maxHeight - paddingV * 2))
        currentIndex--;
    if (scrolldown->isActive()
      && currentIndex < previousSize - 1) currentIndex++;

    lastRenderTime = currentTime;
  }

  /** Render scroll buttons **/
  scrollup->paint(wScale, hScale);
  scrolldown->paint(wScale, hScale);

  if (lineHeight * inputs.size() > (unsigned int)(maxHeight - paddingV * 2)) {
    renderBottomUp(wScale, hScale);
  } else {
    renderTopDown(wScale, hScale);
  }
}

SDL_Color ChatArea::getColor(MessageType t) {
  SDL_Color s = {};
  switch (t) {
    case MessageType::INFO:
      s = { 255, 255, 0, 0xFF };
      return s;
    case MessageType::DANGER:
      s = { 255, 0, 0, 0xFF };
      return s;
    case MessageType::SUCCESS:
      s = { 0, 70, 255, 0xFF };
      return s;
    case MessageType::NORMAL:
      s = { 255, 255, 255, 0xFF };
      return s;
  default:
    s = { 255, 255, 255, 0xFF };
    return s;
  }
}

void ChatArea::renderBottomUp(
  double& wScale,
  double& hScale
) {
  TTF_Font* font = manager.getFont("arial");
  LTexture* tex1 = manager.getTexture("area-line1");

  int leftHeight = maxHeight - paddingV * 2;

  for (int i = currentIndex; i >= 0; i--) {
    // We cannot render empty text.
    if (inputs[i].value.size() == 0) {
      inputs[i].value += " ";
    }

    tex1->loadFromRenderedText(
      font,
      inputs[i].value,
      getColor(inputs[i].type));

    int w, h;
    tex1->queryTexture(w, h);
    if (leftHeight - h >= 0) {
      SDL_Rect destRect = {
        x,
        y + leftHeight - h + paddingV,
        w > maxWidth ? maxWidth : w,
        h};
      tex1->paint(destRect, wScale, hScale);
      leftHeight -= h;
    }
  }
}

void ChatArea::renderTopDown(
  double& wScale,
  double& hScale
) {
  TTF_Font* font = manager.getFont("arial");
  LTexture* tex1 = manager.getTexture("area-line1");

  int height = paddingV;

  for (size_t i = 0; i < inputs.size(); i++) {
    // We cannot render empty text.
    if (inputs[i].value.size() == 0) {
      inputs[i].value += " ";
    }

    tex1->loadFromRenderedText(
      font,
      inputs[i].value,
      getColor(inputs[i].type));

    int w, h;
    tex1->queryTexture(w, h);

    SDL_Rect destRect = {
      x,
      y + height,
      w > maxWidth ? maxWidth : w,
      h};
    tex1->paint(destRect, wScale, hScale);
    height += h;
  }
}
