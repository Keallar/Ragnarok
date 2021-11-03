#pragma once
#include "Bullet.h"
#include "box2d/b2dRootWorldNode.h"

enum class eBulletType {
	playerOrdinary
};

class BulletFactory
{
public:
	static BulletFactory* getInstance();

	Bullet* createBullet(eBulletType type, b2WorldNode* world, Vec2 pos, Vec2 dest);
private:
	//BulletFactory();
	//~BulletFactory();

	Bullet* createPlayerOrdinaryBullet(b2WorldNode* world, Vec2 pos, Vec2 dest);

	static BulletFactory* instance;
};

