#ifndef _CHAT_AREA_ENTITY_H_
#define _CHAT_AREA_ENTITY_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../entities/Entity.h"
#include "../entities/ButtonEntity.h"
#include "../../definitions/ChatDefinitions.h"
#include "../sdl/LTexture.h"
#include "../sdl/SdlAssetsManager.h"

#define SCROLL_LAPSE 100
#define CURSOR_ANIM_LAPSE 700
#define SCROLL_BUTTON_S 18

class ChatArea : public Entity {
	private:
    SdlAssetsManager& manager;
		int x;
		int y;
    int maxWidth;
    int maxHeight;
    int paddingV;
    int lineHeight;
    int currentIndex = 0;
    int previousSize = 0;
    int lastRenderTime = 0;
    std::unique_ptr<ButtonEntity> scrollup;
    std::unique_ptr<ButtonEntity> scrolldown;
    std::vector<Entry> inputs;
    void renderBottomUp(double& wScale, double& hScale);
    void renderTopDown(double& wScale, double& hScale);
    SDL_Color getColor(MessageType t);

	public:
    ChatArea(
      SdlAssetsManager& manager,
      int xpos,
      int ypos,
      int maxWidth,
      int maxHeight,
      int paddingV,
      int lineHeight);
		ChatArea(const ChatArea&) = delete;
    ChatArea& operator=(const ChatArea&) = delete;
		void update(ChatData& chat);
    void handleClick(int xCoord, int yCoord);
    void handleClickClear();
		void paint(const Camera &camera,
			double scaleW, double scaleH) override {}
		void paint(double scaleW, double scaleH) override;
};

#endif
