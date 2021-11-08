#include "SimpleEnemy.h"

USING_NS_CC;

SimpleEnemy::SimpleEnemy() {
	init();
}

SimpleEnemy::~SimpleEnemy() {
}

SimpleEnemy* SimpleEnemy::createSimpleEnemy() {
	auto simpleEnemyObj = create("hero.png", b2BodyType::b2_dynamicBody, 0.f, 0);
	return simpleEnemyObj;
}

SimpleEnemy* SimpleEnemy::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	SimpleEnemy* sprite = new (std::nothrow) SimpleEnemy();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool SimpleEnemy::init() {
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


