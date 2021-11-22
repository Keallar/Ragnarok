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

Bullet* BulletFactory::createBullet(IBulletTypeCreator* bulletCreator, b2WorldNode* world, Vec2 pos, Vec2 dest) {
	return bulletCreator->create(world, pos, dest);
}