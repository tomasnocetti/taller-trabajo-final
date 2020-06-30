#ifndef _PLAYER_VIEW_H_
#define _PLAYER_VIEW_H_

#include "Animation.h"
#include "../entities/Entity.h"
#include "../sdl/SdlAssetsManager.h"
#include "../../definitions/PlayerDefinitions.h"
#include "../../definitions/EquipmentDefinitions.h"
#include "HeadWear.h"
#include "Shield.h"
#include "Weapon.h"

class PlayerView : public Entity {
	public:
		explicit PlayerView(SdlAssetsManager& manager);
    ~PlayerView();
		void init();
		void move(int x, int y) override;
		void paint(double scaleW, double scaleH) override {}
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override;
		void setBodyWear(LTexture* texture);
		void checkRace(PlayerRace race);
		void checkHealth(int health);
		void checkEquipment(EquipmentData equipment);
		PlayerView(const PlayerView&) = delete;
    PlayerView& operator=(const PlayerView&) = delete;

	private:
		SdlAssetsManager& manager;
		std::unique_ptr<Animation> animation;
	  LTexture* head = nullptr;
		HeadWear headWear;
		Shield shield;
		Weapon weapon;
	  SDL_Rect headFrame;
		bool ghost;
};

#endif
