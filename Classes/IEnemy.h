#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class IEnemy : public b2Sprite {
public:
	virtual void setHp(float hp) noexcept;
	virtual void changeHp(float difHp) noexcept;
	virtual float getHp() const noexcept;
	virtual void setSpeed(float speed) noexcept;
	virtual float getSpeed() const noexcept;
	virtual void setDestroyed(bool state) noexcept;
	virtual bool isDestroyed() const ;
	virtual void setDamaged(bool state) noexcept;
	virtual bool isDamaged() const;
protected:
	float _speed;
private:
	float _hp;
	bool _destroyed;
	bool _damaged;
};