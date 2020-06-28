#ifndef _CHAT_CONTROLLER_H_
#define _CHAT_CONTROLLER_H_

#include <SDL2/SDL_ttf.h>
#include "../sdl/SdlAssetsManager.h"
#include "../model/ServerProxy.h"
#include "../../DataDefinitions.h"
#include "../entities/TextInputEntity.h"

class ChatController {
  public:
  	explicit ChatController(ServerProxy& model, SdlAssetsManager& manager);
    ChatController(const ChatController&) = delete;
    ChatController& operator=(const ChatController&) = delete;
    void init();
    void handleEvent(const SDL_Event &e);
    void handleCommand();
    std::vector<Entity*> getEntities();

  private:
    ServerProxy& model;
    bool active = false;
    SDL_Rect src = {
      CHAT_BASE_X,
      CHAT_BASE_Y,
      CHAT_BASE_W,
      CHAT_BASE_H};
    TextInputEntity* userInputField;
    SdlAssetsManager& manager;
    std::vector<Entity*> entities;
};

#endif
