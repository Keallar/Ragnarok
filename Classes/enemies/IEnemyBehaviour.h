#pragma once
#include "IEnemy.h"
#include <string>

class IEnemyBehaviour {
public:
	virtual ~IEnemyBehaviour() {}
	virtual void perform(IEnemy* enemy, float dt) = 0;
	virtual std::string getBehaviourName() const = 0;
protected:
	std::string _name;
	float _stateCooldown;
};
