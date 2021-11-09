#include "ShootingCharacter.h"

const float ShootingCharacter::PLAYER_ATTACK_COOLDOWN = 0.2f;
const float ShootingCharacter::ENEMY_ATTACK_COOLDOWN = 0.5f;

void ShootingCharacter::CreateBulletOnParent(eBulletType type, Vec2 pos, Vec2 dest) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());
	auto bullet = BulletFactory::getInstance()->createBullet(type, world, pos, dest);
	bullets.push_back(bullet);
}

void ShootingCharacter::ShootingCharacterUpdate(float dt) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());

	for (auto bullet : bullets) {
		if (bullet) {
			if (!(bullet->isRemoving())) {
				bullet->update(dt);
				if (bullet->getMoveTime() <= 0) {
					bullet->setOnRemove();
				}
			}
			if (bullet->isRemoving()) {
				world->removeChild(bullet);
				bullets.erase(std::find(bullets.begin(), bullets.end(), bullet));
			}
		}
	}

	if (attackCooldown > 0) {
		attackCooldown -= dt;
	}
}

void ShootingCharacter::cleanFunc() {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());
	for (Bullet* i : bullets) {
		world->removeChild(i);
	}
	bullets.clear();
}