#pragma once
#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(IEnemyType* type, IEnemyBehaviour* behaviour)
	: IEnemy(type, behaviour) {
	init();
}

Enemy::~Enemy() {
}

Enemy* Enemy::create(b2BodyType bodyType, float32 friction, float32 restitution, IEnemyType* type, IEnemyBehaviour* behaviour) {
	Enemy* enemyObj = new (std::nothrow) Enemy(type, behaviour);
	if (enemyObj && enemyObj->initWithFile(type->getFileName())) {
		enemyObj->initBody(bodyType, friction, restitution);
		enemyObj->autorelease();
		enemyObj->setName(type->getName());
		enemyObj->getFixtureDef()->filter = type->getFilter();
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
	setName(_type->getName());
	setHp(_type->getHp());
	setSpeed(_type->getSpeed());
	setDamage(_type->getDamage());
	setSpeed(_type->getSpeed());
	setDamaged(false);
	setDestroyed(false);
	return true;
}
