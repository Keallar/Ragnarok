#pragma once
#include "IEnemyBehaviour.h"

class SimpleIdleBehaviour : public IEnemyBehaviour {
	
public:
	SimpleIdleBehaviour();
	~SimpleIdleBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class FlyingIdleBehaviour : public IEnemyBehaviour {

public:
	FlyingIdleBehaviour();
	~FlyingIdleBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class AbobaIdleBehaviour : public IEnemyBehaviour {

public:
	AbobaIdleBehaviour();
	~AbobaIdleBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class WolfIdleBehaviour : public IEnemyBehaviour {

public:
	WolfIdleBehaviour();
	~WolfIdleBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class BossIdleBehaviour : public IEnemyBehaviour {

public:
	BossIdleBehaviour();
	~BossIdleBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};
