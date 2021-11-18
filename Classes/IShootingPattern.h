#pragma once
#include "ShootingCharacter.h"

class IShootingPattern {
public:
	IShootingPattern(ShootingCharacter* parent) : _parent(parent) {};
	virtual void shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) = 0;
protected:
	ShootingCharacter* _parent;
};

class IdleShootingPattern : public IShootingPattern {
public:
	IdleShootingPattern(ShootingCharacter* parent) : IShootingPattern(parent) {};
	void shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) override;
};

class ShotGunShootingPattern : public IShootingPattern {
public:
	ShotGunShootingPattern(ShootingCharacter* parent) : IShootingPattern(parent) {};
	void shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) override;
};

class CircleShootingPattern : public IShootingPattern {
public:
	CircleShootingPattern(ShootingCharacter* parent) : IShootingPattern(parent) {};
	void shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) override;
};