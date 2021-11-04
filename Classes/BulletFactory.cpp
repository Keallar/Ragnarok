#include "BulletFactory.h"

BulletFactory* BulletFactory::instance = nullptr;

BulletFactory* BulletFactory::getInstance() {
	if (instance != nullptr) {
		return instance;
	}

	instance = new BulletFactory;
	return instance;
}

Bullet* BulletFactory::createBullet(eBulletType type, b2WorldNode* world, Vec2 pos, Vec2 dest) {
	switch (type) {
	case eBulletType::playerOrdinary:
		return createPlayerOrdinaryBullet(world, pos, dest);
	}
}

Bullet* BulletFactory::createPlayerOrdinaryBullet(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::createBullet(pos, dest);
	bullet->setName("playerOrdinary");
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::bullet);
	bullet->getFixtureDef()->filter = filter;
	world->addChild(bullet);
	bullet->setPosition(pos);
	bullet->getBody()->SetGravityScale(0);
	bullet->getBody()->SetLinearVelocity(b2Vec2(dest.x, dest.y));
	return bullet;
}