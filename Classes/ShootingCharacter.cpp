#include "ShootingCharacter.h"
#include "IShootingPattern.h"

const float ShootingCharacter::PLAYER_ATTACK_COOLDOWN = 0.2f;
const float ShootingCharacter::PLAYER_BIG_ATTACK_COOLDOWN = 1;
const float ShootingCharacter::ENEMY_ATTACK_COOLDOWN = 0.5f;
const int ShootingCharacter::PLAYER_BULLET_SPEED = 10;

void ShootingCharacter::createBulletOnParent(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());
	auto bullet = BulletFactory::getInstance()->createBullet(bulletCreator, world, pos, dest);
	bullets.push_back(bullet);
}

void ShootingCharacter::shootingCharacterUpdate(float dt) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());

	/*for (auto bullet : bullets) {
		if (bullet) {
			if (!(bullet->isRemoving())) {
				bullet->update(dt);
			}
			else {
				world->removeChild(bullet);
				bullets.erase(std::find(bullets.begin(), bullets.end(), bullet));
			}
		}
	}*/

	for (auto bullet : bullets) {
		if (bullet) {
			if (!(bullet->isRemoving())) {
				bullet->update(dt);
			}
			if (bullet->isRemoving()) {
				world->removeChild(bullet);
			}
		}
	}

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](Bullet* bullet) { return bullet->isRemoving(); }),
		bullets.end());

	if (_attackCooldown > 0) {
		_attackCooldown -= dt;
	}
}

void ShootingCharacter::cleanFunc() {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());
	for (Bullet* i : bullets) {
		world->removeChild(i);
	}
	bullets.clear();
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