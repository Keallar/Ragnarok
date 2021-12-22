#pragma once
#include "IEnemyBehaviour.h"

class SimpleAgressiveBehaviour : public IEnemyBehaviour {
public:
	SimpleAgressiveBehaviour();
	~SimpleAgressiveBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
private:
	enum eAgressiveState {
		Run,
		Jump
	};
};

class FlyingAgressiveBehaviour : public IEnemyBehaviour {
public:
	FlyingAgressiveBehaviour();
	~FlyingAgressiveBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class AbobaAgressiveBehaviour : public IEnemyBehaviour {
public:
	AbobaAgressiveBehaviour();
	~AbobaAgressiveBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class WolfAgressiveBehaviour : public IEnemyBehaviour {
public:
	WolfAgressiveBehaviour();
	~WolfAgressiveBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};

class BossAgressiveBehaviour : public IEnemyBehaviour {
public:
	BossAgressiveBehaviour();
	~BossAgressiveBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
};