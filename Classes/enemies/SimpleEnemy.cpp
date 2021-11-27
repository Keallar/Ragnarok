#pragma once
#include "SimpleEnemy.h"
#include "box2d/b2dRootWorldNode.h"

SimpleEnemy::SimpleEnemy() {
	//File
	_fileName = "Turtle.png";
	//Animation
	//Idle animation
	Vector<SpriteFrame*> idleAnimFrames;
	idleAnimFrames.reserve(4);
	idleAnimFrames.pushBack(SpriteFrame::create("Turtle.png", Rect(0, 0, 32, 32)));
	idleAnimFrames.pushBack(SpriteFrame::create("Turtle.png", Rect(32, 0, 32, 32)));
	idleAnimFrames.pushBack(SpriteFrame::create("Turtle.png", Rect(64, 0, 32, 32)));
	idleAnimFrames.pushBack(SpriteFrame::create("Turtle.png", Rect(96, 0, 32, 32)));
	Animation* _idleAnimation = Animation::createWithSpriteFrames(idleAnimFrames, 0.13f);
	_idleAnim = Animate::create(_idleAnimation);
	//References
	_enemyName = "SimpleEnemy_";
	_filter.categoryBits = static_cast<uint16>(eColCategory::enemy);
	_filter.maskBits = static_cast<uint16>(eColMask::enemy);
	_hp = 100;
	_damage = 1;
	_speed = 10.f;
	_attackCooldown = 0.5f;
	_bulletSpeed = 10;
}

std::string SimpleEnemy::getTypeName() const {
	return "SimpleEnemy";
}
