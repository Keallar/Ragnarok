#include "ShootingCharacter.h"
#include "IShootingPattern.h"

const float ShootingCharacter::PLAYER_ATTACK_COOLDOWN = 0.2f;
const float ShootingCharacter::PLAYER_BIG_ATTACK_COOLDOWN = 1;
const float ShootingCharacter::ENEMY_ATTACK_COOLDOWN = 0.5f;
const int ShootingCharacter::PLAYER_BULLET_SPEED = 10;
const int ShootingCharacter::PLAYER_HOOK_SPEED = 15;

b2Filter ShootingCharacter::playerPhysMask() {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::playerBullet);
	return filter;
}

b2Filter ShootingCharacter::enemyPhysMask() {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::enemyBullet);
	return filter;
}

b2Filter ShootingCharacter::hookPhysMask() {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::hook);
	return filter;
}

void ShootingCharacter::createBulletOnParent(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest) {
	BulletFactory::getInstance()->createBullet(bulletCreator, pos, dest);
}

void ShootingCharacter::shootingCharacterUpdate(float dt) {
	if (_attackCooldown > 0) {
		_attackCooldown -= dt;
	}
}

void ShootingCharacter::setCooldown(float cooldown) {
	if (cooldown > 0) {
		_attackCooldown = cooldown;
	}
	else {
		_attackCooldown = 0;
	}
}

float ShootingCharacter::getCooldown() {
	return _attackCooldown;
}