#pragma once
#include "Bullet.h"
#include "box2d/b2dRootWorldNode.h"

enum class eBulletType {
	playerOrdinary,
	enemyOrdinary,
	playerBig
};

class BulletFactory
{
public:
	static BulletFactory* getInstance();

	Bullet* createBullet(eBulletType type, b2WorldNode* world, Vec2 pos, Vec2 dest);
private:
	static BulletFactory* instance;
	static int id;

	Bullet* createPlayerOrdinaryBullet(b2WorldNode* world, Vec2 pos, Vec2 dest);

	Bullet* createEnemyOrdinaryBullet(b2WorldNode* world, Vec2 pos, Vec2 dest);

	Bullet* createPlayerBigBullet(b2WorldNode* world, Vec2 pos, Vec2 dest);
};

