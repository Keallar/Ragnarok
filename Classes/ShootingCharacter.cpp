#include "ShootingCharacter.h"

const float ShootingCharacter::PLAYER_ATTACK_COOLDOWN = 0.2f;
const float ShootingCharacter::ENEMY_ATTACK_COLLDOWN = 0.5f;

ShootingCharacter::ShootingCharacter() {
	shootInit();
}

ShootingCharacter::~ShootingCharacter() {

}

void ShootingCharacter::shootInit() {
	attackCooldown = 1.0f;
}

void ShootingCharacter::CreateBulletOnParent(eBulletType type, Vec2 pos, Vec2 dest) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());
	auto bullet = BulletFactory::getInstance()->createBullet(eBulletType::playerOrdinary, world, pos, dest);

	bullets.push_back(bullet);
}

void ShootingCharacter::ShootingCharacterUpdate(float dt) {
	b2WorldNode* world = dynamic_cast<b2WorldNode*>(getParent());

	for (auto bullet : bullets) {
		if (bullet) {
			bullet->update(dt);
			if (bullet->getMoveTime() <= 0) {
				world->removeChild(bullet);
				bullets.erase(std::find(bullets.begin(), bullets.end(), bullet));
			}
		}
	}

	if (attackCooldown > 0) {
		attackCooldown -= dt;
	}
}