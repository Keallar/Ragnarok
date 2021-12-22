#pragma once
#include "box2d/b2dRootWorldNode.h"
#include "Bullet.h"

class ShootingCharacter;

class IBulletTypeCreator {
public:
	virtual Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) = 0;
	IBulletTypeCreator::IBulletTypeCreator(b2Filter filter, ShootingCharacter* parent) : _filter(filter), _parent(parent) {};
protected:
	b2Filter _filter;
	ShootingCharacter* _parent;
};

class IdleBulletCreator : public IBulletTypeCreator {
public:
	IdleBulletCreator::IdleBulletCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class BigBulletCreator : public IBulletTypeCreator {
public:
	BigBulletCreator::BigBulletCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class HookBulletCreator : public IBulletTypeCreator {
public:
	HookBulletCreator::HookBulletCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class IceBulletCreator : public IBulletTypeCreator {
public:
	IceBulletCreator::IceBulletCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class IceBlastCreator : public IBulletTypeCreator {
public:
	IceBlastCreator::IceBlastCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class FireBulletCreator : public IBulletTypeCreator {
public:
	FireBulletCreator::FireBulletCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};

class FireBlastCreator : public IBulletTypeCreator {
public:
	FireBlastCreator::FireBlastCreator(b2Filter filter, ShootingCharacter* parent) : IBulletTypeCreator(filter, parent) {};
	Bullet* create(b2WorldNode* world, Vec2 pos, Vec2 dest) override;
};