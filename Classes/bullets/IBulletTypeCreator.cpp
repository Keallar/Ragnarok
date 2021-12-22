#include "IBulletTypeCreator.h" 
#include "BigBullet.h"
#include "PlayerHookBullet.h"
#include "IceBullet.h"
#include "FireBullet.h"
#include "ShootingCharacter.h"

Bullet* IdleBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::create(world, pos, dest, _filter, _parent);
	return bullet;
}

Bullet* BigBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = BigBullet::create(world, pos, dest, _filter, _parent);
	return bullet;
}

Bullet* HookBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = PlayerHookBullet::create(world, pos, dest, _filter, _parent);
	return bullet;
}

Bullet* IceBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = IceBullet::create(world, pos, dest, _filter, _parent);
	return bullet;
}

Bullet* IceBlastCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = IceBlast::create(world, pos, dest, _filter, _parent);
	return bullet;
}

Bullet* FireBulletCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = FireBullet::create(world, pos, dest, _filter, _parent);
	return bullet;
}

Bullet* FireBlastCreator::create(b2WorldNode* world, Vec2 pos, Vec2 dest) {
	auto bullet = FireBlast::create(world, pos, dest, _filter, _parent);
	return bullet;
}
