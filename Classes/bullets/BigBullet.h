#pragma once
#include "Bullet.h"
class BigBullet : public Bullet {
public:
	static BigBullet* createBullet(Vec2 pos, Vec2 dest);
	static BigBullet* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);

	virtual bool init();
	virtual void update(float dt);
	virtual int getDamage();
};

