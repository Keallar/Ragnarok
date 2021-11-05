#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"
#include "bullet.h"
#include "BulletFactory.h"

class ShootingCharacter : public b2Sprite
{
public:
	ShootingCharacter();
	~ShootingCharacter();

	static const float PLAYER_ATTACK_COOLDOWN;
	static const float ENEMY_ATTACK_COLLDOWN;

	virtual void shoot(Vec2 targetPos) = 0;

	virtual void shootInit();

	void CreateBulletOnParent(eBulletType type, Vec2 pos, Vec2 dest);

	void ShootingCharacterUpdate(float dt);

protected:
	float attackCooldown;

	std::vector<Bullet*> bullets;
};

