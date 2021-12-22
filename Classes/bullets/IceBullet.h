#pragma once
#include "Bullet.h"
#include "ShootingCharacter.h"


class IceBullet : public Bullet, public ShootingCharacter {
public:
	static IceBullet* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent);

	virtual void collideFunc();
	virtual bool init();
	virtual void update(float dt);
	bool isStoped();
	void shoot(cocos2d::Vec2 targetPos, IBulletTypeCreator* bulletCreator) override;

private:
	bool _stoped;
};

class IceBlast : public Bullet {
public:
	static IceBlast* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent);

	virtual bool init();
	virtual void update(float dt);
};

