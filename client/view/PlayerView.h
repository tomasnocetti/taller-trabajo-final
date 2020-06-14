#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "PlayerAnimation.h"
#include "../entities/Entity.h"

class PlayerView : public Entity {
	public:
		PlayerView();
		void init(SdlWindow &window, int x, int y);
		void stand(int xOffset, int yOffset);
		void walk(int xOffset, int yOffset);
		void paint(const Camera &camera);
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;

	private:
		int speed;
	  PlayerAnimation animation;
};

#endif
