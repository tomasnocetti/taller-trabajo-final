#ifndef _ENEMY_VIEW_H_
#define _ENEMY_VIEW_H_

#include "Animation.h"
#include "AnimationTypes.h"
#include "../entities/Entity.h"

class EnemyView : public Entity {
	public:
		EnemyView(int x, int y, Animation* animation);
		void move(int x, int y) override;
		void paint(double scaleW, double scaleH) override {}
    void paint(const Camera &camera, 
    	double scaleW, double scaleH) override;
		EnemyView(const EnemyView&) = delete;
    EnemyView& operator=(const EnemyView&) = delete;
    ~EnemyView();
		
	private:
		std::unique_ptr<Animation> animation;
};

#endif
