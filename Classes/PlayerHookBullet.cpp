#include "PlayerHookBullet.h"
#include "IBulletMoveBehavior.h"

PlayerHookBullet* PlayerHookBullet::_hook = nullptr;

bool PlayerHookBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = HOOK_BULLET_MOVE_TIME;
	_lifeTime = HOOK_BULLET_LIFE_TIME;
	_hooked = false;
	_isOnRemove = false;
	return true;
}

void PlayerHookBullet::update(float dt) {
	if (_hooked) {
		_moveBehavior = new BulletStopBehavior(this);

	}
	ordinaryUpdate(dt);
}

void PlayerHookBullet::collideFunc() {
	_hooked = true;
}

PlayerHookBullet* PlayerHookBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	if (_hook) {
		_hook->setOnRemove();
	}
	PlayerHookBullet* _hook = new (std::nothrow) PlayerHookBullet();
	if (_hook && _hook->initWithFile("BigBullet.png")) {
		_hook->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		_hook->autorelease();
		_hook->init();
		_hook->setCoords(pos, dest);
		_hook->setNewBehavior(new BulletIdleBehavior(_hook));
		_hook->getFixtureDef()->filter = filter;
		_hook->ordinaryOptions(world, pos);
		return _hook;
	}
	CC_SAFE_DELETE(_hook);
	return nullptr;
}

int PlayerHookBullet::getDamage() {
	return 0;
}

bool PlayerHookBullet::isHooked() {
	return _hooked;
}