#include "IBulletTypeCreator.h" 

//WTF
void playerOrdinaryOptions(Bullet* bullet, b2WorldNode* world, Vec2 pos, Vec2 dest) {
	world->addChild(bullet);
	bullet->setPosition(pos);
	bullet->getBody()->SetGravityScale(0);
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

Bullet* PlayerIdleBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::createBullet(pos, dest);
	bullet->setName("bulletPlayerOrdinary");
	playerPhysMask(bullet);
	playerOrdinaryOptions(bullet, world, pos, dest);
	return bullet;
}

Bullet* PlayerBigBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = BigBullet::createBullet(pos, dest);
	bullet->setName("bulletPlayerBig");
	playerPhysMask(bullet);
	playerOrdinaryOptions(bullet, world, pos, dest);
	return bullet;
}

Bullet* EnemyIdleBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::createBullet(pos, dest);
	bullet->setName("bulletEnemyOrdinary");
	enemyPhysMask(bullet);
	world->addChild(bullet);
	bullet->setPosition(pos);
	bullet->getBody()->SetGravityScale(0);
	return bullet;
}