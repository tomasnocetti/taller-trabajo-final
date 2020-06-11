#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "Animation.h"
#include "AnimationTypes.h"
#include "../entities/Entity.h"

class PlayerView : public Entity {
	public:
		PlayerView();
		void init(int x, int y, LTexture texture);
		void stand(int xOffset, int yOffset);
		void walk(int xOffset, int yOffset);
		void paint(int cameraX, int cameraY);
		int getX();
		int getY();
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;
	private:
		int x;
		int y;
		int speed;
	  Animation animation;
};

#endif
