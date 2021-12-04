#pragma once
#include "AbobaEnemy.h"
#include "box2d/b2dRootWorldNode.h"

AbobaEnemy::AbobaEnemy() {
	//File
	_fileName = "PAPAABOBA.png";
	//Animation
	//Idle animation
	_idleAnimFrames.reserve(4);
	_idleAnimFrames.pushBack(SpriteFrame::create("PAPAABOBA_anim.png", Rect(0, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create("PAPAABOBA_anim.png", Rect(64, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create("PAPAABOBA_anim.png", Rect(128, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create("PAPAABOBA_anim.png", Rect(192, 0, 64, 64)));
	//References
	_enemyName = "AbobaEnemy_";
	_filter.categoryBits = static_cast<uint16>(eColCategory::enemy);
	_filter.maskBits = static_cast<uint16>(eColMask::enemy);
	_hp = 100;
	_damage = 1;
	_speed = 10.f;
	_attackCooldown = 0.5f;
	_bulletSpeed = 10;
}

std::string AbobaEnemy::getTypeName() const {
	return "AbobaEnemy";
}
