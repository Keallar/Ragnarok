#pragma once
#include "ShootingCharacter.h"
#include "IEnemyBehaviour.h"
#include "IEnemyType.h"
#include "IEnemyBehaviour.h"

class IEnemy : public ShootingCharacter {
public:
	virtual ~IEnemy();
	void setBehaviour(IEnemyBehaviour* behaviour);
	void setType(IEnemyType* type);
	void setHp(int hp) noexcept;
	void changeHp(float difHp);
	int getHp() const noexcept;
	void setSpeed(float speed) noexcept;
	float getSpeed() const noexcept;
	void setDestroyed(bool state) noexcept;
	bool isDestroyed() const noexcept;
	void setDamaged(bool state) noexcept;
	bool isDamaged() const noexcept;
	void createHpLabel();
	void updateHpLabel();

	virtual void update(float dt);
	virtual void shoot(Vec2 targetPos, eBulletType type);
	virtual void setShootTarget(Vec2 target);

	static int BULLET_SPEED;
private:
	Vec2 _shootTarget;
	int _hp;
	float _speed;
	bool _destroyed;
	bool _damaged;
	Label* hpLabel;
	IEnemyBehaviour* _behaviour;
	IEnemyType* _type;
};