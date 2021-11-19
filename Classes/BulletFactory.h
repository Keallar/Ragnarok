#pragma once
#include "Bullet.h"
#include "box2d/b2dRootWorldNode.h"
#include "IBulletTypeCreator.h"

enum class eBulletType {
	playerOrdinary,
	enemyOrdinary,
	playerBig
};

class BulletFactory
{
public:
	static BulletFactory* getInstance();

	Bullet* createBullet(IBulletTypeCreator* bulletCreator, b2WorldNode* world, Vec2 pos, Vec2 dest);
private:
	static BulletFactory* instance;
	static int id;
};

