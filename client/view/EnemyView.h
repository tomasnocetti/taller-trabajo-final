#ifndef _ENEMY_VIEW_H_
#define _ENEMY_VIEW_H_

#include "Animation.h"
#include "AnimationTypes.h"
#include "../entities/Entity.h"
#include "SkeletonAnimation.h"

class EnemyView : public Entity {
	public:
		EnemyView(int x, int y, Animation* animation);
		//void stand(int xOffset, int yOffset);
		//void walk(int xOffset, int yOffset);
		void paint() override {};
    void paint(const Camera &camera) override;
		EnemyView(const EnemyView&) = delete;
    EnemyView& operator=(const EnemyView&) = delete;
    ~EnemyView();
	private:
		int speed;
	  Animation* animation;
};

#endif
