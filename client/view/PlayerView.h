#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "PlayerAnimation.h"
#include "../entities/Entity.h"

class PlayerView : public Entity {
	public:
		PlayerView();
		void init(int x, int y, SdlWindow &window);
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
