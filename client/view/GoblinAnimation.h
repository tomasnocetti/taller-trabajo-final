#ifndef _GOBLIN_ANIMATION_H_
#define _GOBLIN_ANIMATION_H_

#include "Animation.h"

class GoblinAnimation : public Animation {
	public:
		explicit GoblinAnimation(LTexture* texture);
		GoblinAnimation(const GoblinAnimation&) = delete;
	  GoblinAnimation& operator=(const GoblinAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
