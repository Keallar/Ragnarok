#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(IEnemyBehaviour* behaviour = nullptr) {
	init();
}

Enemy::~Enemy() {
}

Enemy* Enemy::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	Enemy* enemyObj = new (std::nothrow) Enemy();
	if (enemyObj && enemyObj->initWithFile(filename)) {
		enemyObj->initBody(type, friction, restitution);
		enemyObj->autorelease();
		return enemyObj;
	}
	CC_SAFE_DELETE(enemyObj);
	return nullptr;
}

bool Enemy::init() {
	if (!b2Sprite::init()) {
		return false;
	}
	attackCooldown = 0;
	setHp(100);
	setSpeed(10.f);
	setDamaged(false);
	setDestroyed(false);
	return true;
}


