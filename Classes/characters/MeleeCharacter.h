#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class MeleeCharacter {
public:
	MeleeCharacter();

	virtual void hit() = 0;
	
	virtual void meleeInit();
	void update(float dt);
	virtual void cleanHit() = 0;
protected:
	b2Sprite* _meleeHit;

	bool _isMeleeAttack;

	float _hitTime; 
	float _time;

	int _damage;

};