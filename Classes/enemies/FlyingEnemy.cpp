#pragma once
#include "FlyingEnemy.h"
#include "box2d/b2dRootWorldNode.h"

FlyingEnemy::FlyingEnemy() {
	_fileName = "Flying_enemy.png";
	animFrames.reserve(4);	
	animFrames.push_back(SpriteFrame::create(_fileName, Rect(0, 0, 64, 64)));
	animFrames.push_back(SpriteFrame::create(_fileName, Rect(64, 64, 64, 64)));
	animFrames.push_back(SpriteFrame::create(_fileName, Rect(128, 128, 64, 64)));
	animFrames.push_back(SpriteFrame::create(_fileName, Rect(192, 192, 64, 64)));
	_enemyName = "FlyingEnemy_";
	_filter.categoryBits = static_cast<uint16>(eColCategory::enemy);
	_filter.maskBits = static_cast<uint16>(eColMask::enemy);
	_hp = 100;
	_damage = 1;
	_speed = 20.f;
	_attackCooldown = 1.f;
	_bulletSpeed = 10;
}

std::string FlyingEnemy::getTypeName() const {
	return "FlyingEnemy";
}