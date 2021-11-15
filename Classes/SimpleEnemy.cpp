#pragma once
#include "SimpleEnemy.h"
#include "box2d/b2dRootWorldNode.h"

SimpleEnemy::SimpleEnemy() {
	_fileName = "hero.png";
	_enemyName = "SimpleEnemy_";
	_filter.categoryBits = static_cast<uint16>(eColCategory::enemy);
	_filter.maskBits = static_cast<uint16>(eColMask::enemy);
	_hp = 100;
	_damage = 1;
	_speed = 10.f;
	_attackCooldown = 0.5f;
	_bulletSpeed = 10;
}
