#ifndef _CREATE_CONTROLLER_H_
#define _CREATE_CONTROLLER_H_

#include <SDL2/SDL_ttf.h>
#include <map>
#include <utility>
#include "../sdl/SdlAssetsManager.h"
#include "../model/ServerProxy.h"
#include "../../DataDefinitions.h"
#include "../entities/BackgroundEntity.h"
#include "../entities/TextInputEntity.h"
#include "../entities/ButtonEntity.h"

#define C1X 95
#define C1Y 176
#define C2X 208
#define C2Y 176
#define C3X 95
#define C3Y 324
#define C4X 208
#define C4Y 324

#define R1X 494
#define R1Y 176
#define R2X 607
#define R2Y 176
#define R3X 494
#define R3Y 324
#define R4X 607
#define R4Y 324

#define BTN_WIDTH_S 108
#define BTN_HEIGHT_S 146
#define SEL_HEIGHT 294
#define SEL_WIDTH 217

#define BTN_POS_X 319
#define BTN_POS_Y 510
#define BTN_POS_W 165
#define BTN_POS_H 49

using uniqBut = std::shared_ptr<ButtonEntity>;
using classItem = std::pair<PlayerClass, std::shared_ptr<ButtonEntity>>;
using raceItem = std::pair<PlayerRace, std::shared_ptr<ButtonEntity>>;


class CreateController {
  public:
  	explicit CreateController(ServerProxy& model, SdlAssetsManager& manager);
    CreateController(const CreateController&) = delete;
    CreateController& operator=(const CreateController&) = delete;
    void init();
    void create();
    void handleEvent(const SDL_Event &e);
    EntityList &getEntities();

  private:
    void initElements();
    ServerProxy& model;
    SdlAssetsManager& manager;
    std::map<PlayerClass, uniqBut> activeClass;
    std::map<PlayerRace, uniqBut> activeRace;
    std::shared_ptr<TextInputEntity> userInputField;
    std::shared_ptr<TextInputEntity> passwordInputField;
    uniqBut createButton;
    EntityList screens;
};

#endif
