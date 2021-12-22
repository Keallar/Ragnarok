#pragma once
#include "Bullet.h"
#include "ShootingCharacter.h"

class PlayerHookBullet : public Bullet {
public:
	static PlayerHookBullet* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter);

	virtual void collideFunc();
	virtual bool init();
	virtual void update(float dt);
	virtual int getDamage();
	bool isHooked();
	void setVelDest(b2Vec2 dest);
	b2Vec2 getVelDest();

private:
	static PlayerHookBullet* _hook;
	bool _hooked;
	b2Vec2 _velDest;
};

