#ifndef _CHAT_VIEWPORT_H_
#define _CHAT_VIEWPORT_H_

#include <vector>
#include "../sdl/SdlWindow.h"
#include "../sdl/SdlViewport.h"
#include "../../definitions/ChatDefinitions.h"
#include "../entities/Entity.h"

class ChatViewport : public SdlViewport {
  public:
	  ChatViewport(
      SdlWindow& window,
      int x = CHAT_BASE_X,
      int y = CHAT_BASE_Y,
      int w = CHAT_BASE_W,
      int h = CHAT_BASE_H);
    ChatViewport(const ChatViewport&) = delete;
    ChatViewport& operator=(const ChatViewport&) = delete;
    void paint(EntityList& entities);
		~ChatViewport();
};

#endif
