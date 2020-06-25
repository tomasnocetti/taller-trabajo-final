#ifndef _PLAYER_ANIMATION_H_
#define _PLAYER_ANIMATION_H_

#include <string>
#include "Animation.h"

class PlayerAnimation : public Animation {
	public:
		explicit PlayerAnimation(LTexture* texture);
		PlayerAnimation(const PlayerAnimation&) = delete;
	  PlayerAnimation& operator=(const PlayerAnimation&) = delete;
		void changeTexture(LTexture* texture);

	private:
		void cropAnimationFrames();
};

#endif
