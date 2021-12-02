#pragma once
#include "box2d/b2dRootWorldNode.h"
#include "Bullet.h"

class IBulletTypeCreator {
public:
	virtual Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) = 0;

	b2Filter playerPhysMask();
	b2Filter enemyPhysMask();
	b2Filter hookPhysMask();
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

class PlayerHookBulletCreator : public IBulletTypeCreator {
public:
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class PlayerIceBulletCreator : public IBulletTypeCreator {
public:
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class PlayerIceBlastCreator : public IBulletTypeCreator {
public:
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

