#include "BulletFactory.h"
#include "BigBullet.h"
BulletFactory* BulletFactory::instance = nullptr;
int BulletFactory::id = -1;

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
	case eBulletType::enemyOrdinary:
		return createEnemyOrdinaryBullet(world, pos, dest);
	case eBulletType::playerBig:
		return createPlayerBigBullet(world, pos, dest);
	default:
		break;
	}
}

void playerOrdinaryOptions(Bullet* bullet, b2WorldNode* world, Vec2 pos, Vec2 dest) {
	world->addChild(bullet);
	bullet->setPosition(pos);
	bullet->getBody()->SetGravityScale(0);
	bullet->getBody()->SetLinearVelocity(b2Vec2(dest.x, dest.y));
}

void playerPhysMask(Bullet* bullet) {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::playerBullet);
	bullet->getFixtureDef()->filter = filter;
}

void enemyPhysMask(Bullet* bullet) {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::enemyBullet);
	bullet->getFixtureDef()->filter = filter;
}

Bullet* BulletFactory::createPlayerOrdinaryBullet(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::createBullet(pos, dest);
	bullet->setName("bulletPlayerOrdinary");
	playerPhysMask(bullet);
	playerOrdinaryOptions(bullet, world, pos, dest);
	return bullet;
}

Bullet* BulletFactory::createEnemyOrdinaryBullet(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::createBullet(pos, dest);
	bullet->setName("bulletEnemyOrdinary");
	enemyPhysMask(bullet);
	world->addChild(bullet);
	bullet->setPosition(pos);
	bullet->getBody()->SetGravityScale(0);
	bullet->getBody()->SetLinearVelocity(b2Vec2(dest.x, dest.y));
	return bullet;
}

Bullet* BulletFactory::createPlayerBigBullet(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = BigBullet::createBullet(pos, dest);
	bullet->setName("bulletPlayerBig");
	playerPhysMask(bullet);
	playerOrdinaryOptions(bullet, world, pos, dest);
	return bullet;
}