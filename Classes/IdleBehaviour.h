#pragma once
#include "IEnemyBehaviour.h"

enum class eIdleState {
	Sleep,
	MoveLeft,
	MoveRight
};

class IdleBehaviour : public IEnemyBehaviour {
public:
	~IdleBehaviour() {}
	void perform(IEnemy* enemy) override;
	std::string getBehaviourName() const override;
private:
	eIdleState _idleState;
	int _startPos;
	bool _completed;
};