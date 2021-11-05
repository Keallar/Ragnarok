#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class IEnemy : public b2Sprite {
public:
	virtual void setHp(int hp) noexcept;
	virtual void changeHp(float difHp) noexcept;
	virtual int getHp() const noexcept;
	virtual void setSpeed(float speed) noexcept;
	virtual float getSpeed() const noexcept;
	virtual void setDestroyed(bool state) noexcept;
	virtual bool isDestroyed() const noexcept;
	virtual void setDamaged(bool state) noexcept;
	virtual bool isDamaged() const noexcept;
	virtual void createHpLabel();
	virtual void updateHpLabel();
protected:

private:
	int _hp;
	float _speed;
	bool _destroyed;
	bool _damaged;
	Label* hpLabel;
};