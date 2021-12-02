#pragma once
#include "IEnemyBehaviour.h"

class AgressiveBehaviour : public IEnemyBehaviour {
public:
	~AgressiveBehaviour() {}
	void perform(IEnemy* enemy, float dt) override;
	std::string getBehaviourName() const override;
};