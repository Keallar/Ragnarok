#pragma once
#include "Bullet.h"
class BigBullet : public Bullet {
public:
	static BigBullet* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent);

	virtual bool init();
	virtual void update(float dt);
};

