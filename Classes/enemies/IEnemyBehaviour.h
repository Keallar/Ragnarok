#pragma once
#include "IEnemy.h"
#include <string>

class IEnemyBehaviour {
public:
	virtual ~IEnemyBehaviour() {}
	virtual void perform(IEnemy* enemy, Vec2 targetPos,float dt) = 0;
	virtual std::string getBehaviourName() const = 0;
protected:
	enum class eIdleState {
		Sleep,
		MoveRight,
		MoveLeft
	};

	std::string _name;
	float _stateCooldown;
	int _state;
};
