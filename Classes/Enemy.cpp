#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(IEnemyBehaviour* behaviour, IEnemyType* type) 
	: IEnemy(behaviour, type) {
	init();
}

Enemy::~Enemy() {
}

Enemy* Enemy::create(const std::string& filename, b2BodyType bodyType, float32 friction, float32 restitution, IEnemyBehaviour* behaviour, IEnemyType* type) {
	Enemy* enemyObj = new (std::nothrow) Enemy(behaviour, type);
	if (enemyObj && enemyObj->initWithFile(filename)) {
		enemyObj->initBody(bodyType, friction, restitution);
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
	/*if (!_behaviour) {
		return false;
	}*/
	if (!_type) {
		return false;
	}
	setHp(_type->getHp());
	setSpeed(_type->getSpeed());
	setDamage(_type->getDamage());
	setSpeed(_type->getSpeed());
	setDamaged(false);
	setDestroyed(false);
	return true;
}
