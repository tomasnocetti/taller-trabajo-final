#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "../sdl/SdlWindow.h"
#include "Animation.h"

class PlayerView {
	public:
		PlayerView(int x, int y, SdlWindow &window);
		void paint();
		void moveX(int speed);
		void moveY(int speed);
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;
	private:
		int x;
		int y;
	  Animation animation;
	  char lastEvent;
};

#endif
