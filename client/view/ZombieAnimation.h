#ifndef _ZOMBIE_ANIMATION_H_
#define _ZOMBIE_ANIMATION_H_

#include <string>
#include "Animation.h"

class ZombieAnimation : public Animation {
	public:
		explicit ZombieAnimation(LTexture* texture);
		ZombieAnimation(const ZombieAnimation&) = delete;
	  ZombieAnimation& operator=(const ZombieAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
