#ifndef _ENEMY_VIEW_H_
#define _ENEMY_VIEW_H_

#include "Animation.h"
#include "AnimationTypes.h"
#include "../entities/Entity.h"
#include "SkeletonAnimation.h"

class EnemyView : public Entity {
	public:
		EnemyView(int x, int y, Animation* animation, SdlWindow &window);
		//void stand(int xOffset, int yOffset);
		//void walk(int xOffset, int yOffset);
		void paint(const Camera &camera);
		EnemyView(const EnemyView&) = delete;
    EnemyView& operator=(const EnemyView&) = delete;
    ~EnemyView();
	private:
		int speed;
	  Animation* animation;
};

#endif
