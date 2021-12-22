#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"
#include "BulletFactory.h"

class IShootingPattern;

class ShootingCharacter {
public:
	virtual void shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) = 0;
	void createBulletOnParent(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest);
	void ShootingCharacter::shootingCharacterUpdate(float dt);

	float getCooldown();
	int getDamage();
	void setCooldown(float cooldown);
	void setDamage(int damage);

	static const float PLAYER_ATTACK_COOLDOWN;
	static const float PLAYER_BIG_ATTACK_COOLDOWN;
	static const float ENEMY_ATTACK_COOLDOWN;
	static const int PLAYER_BULLET_SPEED;
	static const int PLAYER_HOOK_SPEED;

	static b2Filter playerPhysMask();
	static b2Filter enemyPhysMask();
	static b2Filter hookPhysMask();

protected:
	int _bulletDamage;
	float _attackCooldown;
	IShootingPattern* _shootingPattern;
};

