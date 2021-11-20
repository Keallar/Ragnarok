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
private:
	eIdleState _idleState;
	bool _completed;
};