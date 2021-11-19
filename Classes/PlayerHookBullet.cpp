#include "PlayerHookBullet.h"
#include "IBulletMoveBehavior.h"

PlayerHookBullet* PlayerHookBullet::_hook = nullptr;

bool PlayerHookBullet::init() {
	if (!b2Sprite::init()) {
		return false;
	}

	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = HOOK_BULLET_MOVE_TIME;
	_lifeTime = HOOK_BULLET_MOVE_TIME;
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

PlayerHookBullet* PlayerHookBullet::createBullet(Vec2 pos, Vec2 dest) {
	if (_hook) {
		_hook->setOnRemove();
	}
	_hook = PlayerHookBullet::create("BigBullet.png", b2BodyType::b2_dynamicBody, 0.f, 0);
	_hook->setCoords(pos, dest);
	_hook->setNewBehavior(new BulletIdleBehavior(_hook));
	return _hook;
}

PlayerHookBullet* PlayerHookBullet::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	PlayerHookBullet* sprite = new (std::nothrow) PlayerHookBullet();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

int PlayerHookBullet::getDamage() {
	return 0;
}