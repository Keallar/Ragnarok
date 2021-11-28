#pragma once
#include "Enemy.h"

USING_NS_CC;

int Enemy::id = -1;

Enemy::Enemy(IEnemyType* type, IEnemyBehaviour* behaviour)
	: IEnemy(type, behaviour) {
	init();
}

Enemy::~Enemy() {
}

Enemy* Enemy::create(Node* node, Vec2 pos, IEnemyType* type, IEnemyBehaviour* behaviour) {
	id++;
	Enemy* enemyObj = new (std::nothrow) Enemy(type, behaviour);
	if (enemyObj && enemyObj->initWithFile(type->getFileName())) {
		enemyObj->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		enemyObj->autorelease();
		enemyObj->setName(type->getName());
		enemyObj->getFixtureDef()->filter = type->getFilter();
		enemyObj->setName(enemyObj->getName() + std::to_string(id));
		node->addChild(enemyObj);
		enemyObj->getBody()->SetFixedRotation(true);
		enemyObj->setPosition(pos);
		enemyObj->createHpLabel();
		Animation* idleAnimation = Animation::createWithSpriteFrames(type->getIdleFrames(), 0.13f);
		Animate* idleAnim = Animate::create(idleAnimation);
		Action* idleAction = RepeatForever::create(idleAnim);
		//enemyObj->runAction(idleAction);
		return enemyObj;
	}
	CC_SAFE_DELETE(enemyObj);
	return nullptr;
}

bool Enemy::init() {
	if (!b2Sprite::init()) {
		return false;
	}
	if (!_behaviour) {
		return false;
	}
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
