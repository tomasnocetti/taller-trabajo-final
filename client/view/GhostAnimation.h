#ifndef _GHOST_ANIMATION_H_
#define _GHOST_ANIMATION_H_

#include <string>
#include "Animation.h"

class GhostAnimation : public Animation {
	public:
		explicit GhostAnimation(LTexture* texture);
		GhostAnimation(const GhostAnimation&) = delete;
	  GhostAnimation& operator=(const GhostAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
