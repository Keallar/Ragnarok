#pragma once
#include "FlyingEnemy.h"
#include "box2d/b2dRootWorldNode.h"

FlyingEnemy::FlyingEnemy() {
	//File
	_fileName = "Flying_enemy.png";
	//Animation
	//Idle animation
	_idleAnimFrames.reserve(4);
	_idleAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(0, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(64, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(128, 0, 64, 64)));
	_idleAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(192, 0, 64, 64)));
	//Move right animation 
	_moveRightAnimFrames.reserve(4);
	_moveRightAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(0, 128, 64, 64)));
	_moveRightAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(64, 128, 64, 64)));
	_moveRightAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(128, 128, 64, 64)));
	_moveRightAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(192, 128, 64, 64)));
	//Move left animation
	_moveLeftAnimFrames.reserve(4);
	_moveLeftAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(0, 192, 64, 64)));
	_moveLeftAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(64, 192, 64, 64)));
	_moveLeftAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(128, 192, 64, 64)));
	_moveLeftAnimFrames.pushBack(SpriteFrame::create("Flying_enemy_anim.png", Rect(192, 192, 64, 64)));
	//References
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
