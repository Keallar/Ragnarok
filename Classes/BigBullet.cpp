#include "BigBullet.h"
#include "IBulletMoveBehavior.h"

bool BigBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = BIG_BULLET_MOVE_TIME;
	_lifeTime = BIG_BULLET_MOVE_TIME;
	_isOnRemove = false;
	return true;
}

void BigBullet::update(float dt) {
	ordinaryUpdate(dt);
}

BigBullet* BigBullet::createBullet(Vec2 pos, Vec2 dest) {
	auto bullet = BigBullet::create("BigBullet.png", b2BodyType::b2_dynamicBody, 0.f, 0);
	bullet->init();
	bullet->setCoords(pos, dest);
	bullet->setNewBehavior(new BulletIdleBehavior(bullet));
	return bullet;
}

BigBullet* BigBullet::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	BigBullet* sprite = new (std::nothrow) BigBullet();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

int BigBullet::getDamage() {
	return BIG_BULLET_DAMAGE;
}