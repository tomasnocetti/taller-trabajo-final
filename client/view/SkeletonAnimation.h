#ifndef _SKEL_ANIMATION_H_
#define _SKEL_ANIMATION_H_

#include "Animation.h"

class SkeletonAnimation : public Animation {
	public:
		SkeletonAnimation();
		SkeletonAnimation(const SkeletonAnimation&) = delete;
	  SkeletonAnimation& operator=(const SkeletonAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
