#include "PlayerHookBullet.h"
#include "ShootingCharacter.h"

PlayerHookBullet* PlayerHookBullet::_hook = nullptr;

bool PlayerHookBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	
	initVars("PlayerHookBullet");

	_startedMove = false;
	_hooked = false;
	_velDest = { 0, 0 };
	_isOnRemove = false;
	return true;
}

void PlayerHookBullet::update(float dt) {
	if (_hooked) {
		getBody()->SetLinearVelocity(b2Vec2(0, 0));
	}
	if (!_hooked && _moveTime <= 0) {
		setOnRemove();
	}
	Bullet::update(dt);
}

void PlayerHookBullet::collideFunc() {
	_hooked = true;
}

PlayerHookBullet* PlayerHookBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent) {
	if (_hook) {
		_hook->setOnRemove();
	}
	PlayerHookBullet* _hook = new (std::nothrow) PlayerHookBullet();
	_hook->init();
	if (_hook && _hook->initWithFile(_hook->_fileName)) {
		_hook->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		_hook->autorelease();
		//_hook->init();
		_hook->setCoords(pos, dest);
		_hook->_parent = parent;
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

void PlayerHookBullet::setVelDest(b2Vec2 dest) {
	_velDest = dest;
}

b2Vec2 PlayerHookBullet::getVelDest() {
	return _velDest;
}