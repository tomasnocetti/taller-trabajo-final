#ifndef _ENEMY_VIEW_H_
#define _ENEMY_VIEW_H_

#include "Animation.h"
#include "AnimationTypes.h"
#include "../entities/Entity.h"

class EnemyView : public Entity {
	public:
		EnemyView(int x, int y, Animation* animation);
		//void stand(int xOffset, int yOffset);
		void move(int xOffset, int yOffset);
		void paint(double scaleW, double scaleH) override {};
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override;
		EnemyView(const EnemyView&) = delete;
    EnemyView& operator=(const EnemyView&) = delete;
    ~EnemyView();
	private:
	  Animation* animation;
};

#endif
