#pragma once
#include "Bullet.h"
#include "ShootingCharacter.h"

class PlayerHookBullet : public Bullet {
public:
	static PlayerHookBullet* createBullet(Vec2 pos, Vec2 dest);
	static PlayerHookBullet* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);

	virtual void collideFunc();
	virtual bool init();
	virtual void update(float dt);
	virtual int getDamage();
	bool isHooked();

private:
	static PlayerHookBullet* _hook;
	bool _hooked;
};

