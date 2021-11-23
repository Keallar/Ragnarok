#include "IBulletTypeCreator.h" 
#include "BigBullet.h"
#include "PlayerHookBullet.h"

b2Filter IBulletTypeCreator::playerPhysMask() {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::playerBullet);
	return filter;
}

b2Filter IBulletTypeCreator::enemyPhysMask() {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::enemyBullet);
	return filter;
}

b2Filter IBulletTypeCreator::hookPhysMask() {
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::bullet);
	filter.maskBits = static_cast<uint16>(eColMask::hook);
	return filter;
}

Bullet* PlayerIdleBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::create(world, pos, dest, playerPhysMask());
	return bullet;
}

Bullet* PlayerBigBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = BigBullet::create(world, pos, dest, playerPhysMask());
	return bullet;
}

Bullet* EnemyIdleBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::create(world, pos, dest, enemyPhysMask());
	return bullet;
}

Bullet* PlayerHookBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = PlayerHookBullet::create(world, pos, dest, hookPhysMask());
	return bullet;
}