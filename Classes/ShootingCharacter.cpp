#include "ShootingCharacter.h"
#include "IShootingPattern.h"

const float ShootingCharacter::PLAYER_ATTACK_COOLDOWN = 0.2f;
const float ShootingCharacter::PLAYER_BIG_ATTACK_COOLDOWN = 1;
const float ShootingCharacter::ENEMY_ATTACK_COOLDOWN = 0.5f;
const int ShootingCharacter::PLAYER_BULLET_SPEED = 10;

void ShootingCharacter::createBulletOnParent(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());
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