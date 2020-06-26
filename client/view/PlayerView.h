#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "PlayerAnimation.h"
#include "GhostAnimation.h"
#include "../entities/Entity.h"
#include "HeadWear.h"
#include "Shield.h"

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
		void setShield(Shield shield);
		void setGhostAnimation(LTexture* texture);
		void setPlayerAnimation(LTexture* texture);
		bool ghostState();
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;

	private:
	  Animation* animation = nullptr;
	  LTexture* head = nullptr;
		HeadWear headWear;
		Shield shield;
	  SDL_Rect headFrame;
		bool ghost;
};

#endif
