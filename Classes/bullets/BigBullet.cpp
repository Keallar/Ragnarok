#include "BigBullet.h"
#include "ShootingCharacter.h"

bool BigBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	
	initVars("BigBullet");

	_startedMove = false;
	_isOnRemove = false;
	return true;
}

void BigBullet::update(float dt) {
	Bullet::update(dt);
}

BigBullet* BigBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent) {
	BigBullet* bullet = new (std::nothrow) BigBullet();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->_parent = parent;
		bullet->_damage = parent->getDamage();
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}