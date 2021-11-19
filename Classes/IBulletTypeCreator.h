#pragma once
#include "box2d/b2dRootWorldNode.h"
#include "Bullet.h"
#include "BigBullet.h"

class IBulletTypeCreator {
public:
	virtual Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) = 0;
};

class PlayerIdleBulletCreator : public IBulletTypeCreator {
public:
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class PlayerBigBulletCreator : public IBulletTypeCreator {
public:
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class EnemyIdleBulletCreator : public IBulletTypeCreator {
public:
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

