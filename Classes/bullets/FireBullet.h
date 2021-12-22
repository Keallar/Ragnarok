#pragma once
#include "Bullet.h"
#include "ShootingCharacter.h"

class FireBullet : public Bullet, ShootingCharacter	 {
public:
	FireBullet() : Bullet() {};
	static FireBullet* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent);

	bool init() override;
	void update(float dt) override;

	void shoot(cocos2d::Vec2 targetPos, IBulletTypeCreator* bulletCreator) override;
private:
	void setCooldown();
	int _fireCount; //created fires
	float _attackConstCooldown;
};

class FireBlast : public Bullet {
public:
	static FireBlast* create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent);

	void move(float dt) override;

	bool init() override;
	void update(float dt) override;

private:
	void setAngleMoveParam();
	Vec2 _moveDest;
	double _moveAngle;
};