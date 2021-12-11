#include "BigBullet.h"

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

BigBullet* BigBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	BigBullet* bullet = new (std::nothrow) BigBullet();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

int BigBullet::getDamage() {
	return BIG_BULLET_DAMAGE;
}