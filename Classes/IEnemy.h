#pragma once
#include "ShootingCharacter.h"

class IEnemy : public ShootingCharacter {
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

	virtual void update(float dt);
	virtual void shoot(Vec2 targetPos);
	virtual void setShootTarget(Vec2 target);

	static int BULLET_SPEED;
private:
	Vec2 _shootTarget;
	int _hp;
	float _speed;
	bool _destroyed;
	bool _damaged;
	Label* hpLabel;
};