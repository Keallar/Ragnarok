#include "IShootingPattern.h"
#include <cmath>

void IdleShootingPattern::shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) {
	
	_parent->createBulletOnParent(bulletCreator, pos, dest);
}

void ShotGunShootingPattern::shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) {

	_parent->createBulletOnParent(bulletCreator, Vec2(pos.x -5, pos.y), dest);
	_parent->createBulletOnParent(bulletCreator, Vec2(pos.x +5, pos.y), dest);
}

void CircleShootingPattern::shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) {
	float a = -0.13;
	for (int i = -6; i < 6; i++) {
		Vec2 newDest = dest;
		newDest.rotate(Vec2(), a * i);
		_parent->createBulletOnParent(bulletCreator, pos, newDest);
	}
}

void TripleShootingPattern::shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) {
	float a = -0.15;
	for (int i = -1; i < 2; i++) {
		Vec2 newDest = dest;
		newDest.rotate(Vec2(), a * i);
		_parent->createBulletOnParent(bulletCreator, pos, newDest);
	}
}

void ParalRevShootingPattern::shoot(Vec2 pos, Vec2 dest, IBulletTypeCreator* bulletCreator) {
	Vec2 newDest = dest;
	newDest.rotate(Vec2(), 0.9f);
	newDest.normalize();
	newDest *= _distance / 2;
	Vec2 pos1 = pos + newDest;
	Vec2 pos2 = pos - newDest;
	//Vec2 dest2 = dest;
	//dest2 *= -1;
	//Vec2 dest1 = dest;
	_parent->createBulletOnParent(bulletCreator, pos1, dest);
	_parent->createBulletOnParent(bulletCreator, pos2, dest);
}