#pragma once
#include "IEnemyBehaviour.h"

class AgressiveBehaviour : public IEnemyBehaviour {
public:
	AgressiveBehaviour();
	~AgressiveBehaviour() {}
	void perform(IEnemy* enemy, Vec2 targetPos, float dt) override;
	std::string getBehaviourName() const override;
private:
	float _moveCooldown;
};