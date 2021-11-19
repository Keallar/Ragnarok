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
	dest = Vec2(1, 0);
	float a = M_PI * 2 / 27;
	for (int i = 0; i <= 12; i ++) {
		float acos = cos(a * i);
		float asin = sin(a * i);
		float x = dest.x * acos - dest.y * asin;
		float y = dest.x * asin - dest.y * acos;
		Vec2 newDest = Vec2(x, y);
		//newDest.normalize();
		newDest *= _parent->PLAYER_BULLET_SPEED;
		_parent->createBulletOnParent(bulletCreator, pos, newDest);
	}
}
