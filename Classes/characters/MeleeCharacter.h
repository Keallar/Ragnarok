#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class MeleeHit : public b2Sprite {
public:
	static MeleeHit* create(int damage);

	int getDamage();
private:
	int _damage;
};

class MeleeCharacter {
public:
	MeleeCharacter();

	virtual void hit() = 0;
	
	virtual void meleeInit();
	void update(float dt);
	virtual void cleanHit() = 0;

	int getMeleeDamage() const;
protected:
	MeleeHit* _meleeHit;
	bool _isMeleeAttack;
	float _hitTime; 
	float _time;
	int _damage;
};