#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"
#include "bullet.h"
#include "BulletFactory.h"

class ShootingCharacter : public b2Sprite {
public:
	virtual void shoot(Vec2 targetPos, eBulletType type) = 0;
	void createBulletOnParent(eBulletType type, Vec2 pos, Vec2 dest);
	void shootingCharacterUpdate(float dt);
	void cleanFunc();

	static const float PLAYER_ATTACK_COOLDOWN;
	static const float PLAYER_BIG_ATTACK_COOLDOWN;
	static const float ENEMY_ATTACK_COOLDOWN;
protected:
	float attackCooldown;

	std::vector<Bullet*> bullets;
};

