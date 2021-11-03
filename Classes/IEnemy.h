#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class IEnemy : public b2Sprite {
public:
	virtual void setHp(float& hp);
	virtual float getHp() const ;
	virtual void setDestroyed(bool& state);
	virtual bool isDestroyed() const ;
	virtual void setDamaged(bool& state);
	virtual bool isDamaged() const;
private:
	float _hp;
	float _speed;
	bool _destroyed;
	bool _damaged;
};