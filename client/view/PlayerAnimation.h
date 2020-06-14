#ifndef _PLAYER_ANIMATION_H_
#define _PLAYER_ANIMATION_H_

#include <string>
#include "Animation.h"

class PlayerAnimation : public Animation {
	public:
		PlayerAnimation();
		PlayerAnimation(const PlayerAnimation&) = delete;
	  PlayerAnimation& operator=(const PlayerAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
