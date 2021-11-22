#pragma once
#include "Bullet.h"

class IBulletMoveBehavior {
public:
	IBulletMoveBehavior(Bullet* parent);
	virtual ~IBulletMoveBehavior() {};

	virtual void move(float dt) = 0;
protected:

	bool _startedMove;
	Bullet* _parent;
	float _timer;
};

class BulletIdleBehavior : public IBulletMoveBehavior {
public:
	BulletIdleBehavior(Bullet* parent) : IBulletMoveBehavior(parent) {};
	void move(float dt) override;
};