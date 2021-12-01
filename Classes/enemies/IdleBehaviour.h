#pragma once
#include "IEnemyBehaviour.h"

class IdleBehaviour : public IEnemyBehaviour {
	enum class eIdleState {
		Sleep,
		MoveRight,
		MoveLeft
	};
public:
	IdleBehaviour();
	~IdleBehaviour() {}
	void perform(IEnemy* enemy, float dt) override;
	std::string getBehaviourName() const override;
private:
	eIdleState _idleState;
	int _startPos;
	bool _completed;
	int _state;
};