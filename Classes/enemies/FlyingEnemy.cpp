#pragma once
#include "FlyingEnemy.h"
#include "box2d/b2dRootWorldNode.h"

FlyingEnemy::FlyingEnemy() {
	//File
	_fileName = "Flying_enemy.png";
	//Animation
	//Idle animation
	animFrames.reserve(4);	
	Vector<SpriteFrame*> idleAnimFrames;
	idleAnimFrames.reserve(4);
	idleAnimFrames.pushBack(SpriteFrame::create("Tur_idle_anim.png", Rect(0, 0, 64, 64)));
	idleAnimFrames.pushBack(SpriteFrame::create("Tur_idle_anim.png", Rect(64, 0, 64, 64)));
	idleAnimFrames.pushBack(SpriteFrame::create("Tur_idle_anim.png", Rect(128, 0, 64, 64)));
	idleAnimFrames.pushBack(SpriteFrame::create("Tur_idle_anim.png", Rect(192, 0, 64, 64)));
	Animation* _idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.13f);
	Animate* _idleAnim = Animate::create(_idleAnimation);
	_idleAction = RepeatForever::create(_idleAnim);
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