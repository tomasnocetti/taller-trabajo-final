#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "PlayerAnimation.h"
#include "../entities/Entity.h"

class PlayerView : public Entity {
	public:
		PlayerView();
    ~PlayerView();
		void init(LTexture* texture, int x, int y);
		void stand(int xOffset, int yOffset);
		void walk(int xOffset, int yOffset);
		void paint() override {}
    void paint(const Camera &camera) override;
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;
	private:
		int speed;
	  PlayerAnimation* animation;
};

#endif
