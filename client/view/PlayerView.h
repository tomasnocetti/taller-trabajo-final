#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "PlayerAnimation.h"
#include "../entities/Entity.h"
#include "HeadWear.h"

class PlayerView : public Entity {
	public:
		PlayerView();
    ~PlayerView();
		void init(LTexture* texture);
		void move(int x, int y) override;
		void paint(double scaleW, double scaleH) override {}
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override;
    void setHead(LTexture* head);
		void setHeadWear(HeadWear headWear);
		void setBodyWear(LTexture* texture);
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;

	private:
	  Animation* animation = nullptr;
	  LTexture* head = nullptr;
		HeadWear headWear;
	  SDL_Rect headFrame;
};

#endif
