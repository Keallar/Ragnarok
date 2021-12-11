#pragma once
#include "Bullet.h"
#include "ShootingCharacter.h"

class FireBullet : public Bullet, ShootingCharacter	 {
public:
	FireBullet() : Bullet() {};
	static FireBullet* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter);

	bool init() override;
	void update(float dt) override;
	int getDamage() override;

	void shoot(cocos2d::Vec2 targetPos, IBulletTypeCreator* bulletCreator) override;
private:
	int _fireCount; //created fires
};

class FireBlast : public Bullet {
public:
	static FireBlast* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter);

	void move(float dt) override;

	bool init() override;
	void update(float dt) override;
	int getDamage() override;

private:
	Vec2 _moveDest;
};