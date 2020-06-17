#ifndef _SPIDER_ANIMATION_H_
#define _SPIDER_ANIMATION_H_

#include "Animation.h"

class SpiderAnimation : public Animation {
	public:
		explicit SpiderAnimation(LTexture* texture);
		SpiderAnimation(const SpiderAnimation&) = delete;
	  SpiderAnimation& operator=(const SpiderAnimation&) = delete;

	private:
		void cropAnimationFrames();
};

#endif
