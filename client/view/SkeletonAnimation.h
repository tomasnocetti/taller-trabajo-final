#ifndef _SKEL_ANIMATION_H_
#define _SKEL_ANIMATION_H_

#include "Animation.h"

class SkeletonAnimation : public Animation {
	public:
		explicit SkeletonAnimation(LTexture* texture);
		SkeletonAnimation(const SkeletonAnimation&) = delete;
	  SkeletonAnimation& operator=(const SkeletonAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
