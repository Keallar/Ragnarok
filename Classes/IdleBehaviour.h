#pragma once
#include "IEnemyBehaviour.h"

class IdleBehaviour : public IEnemyBehaviour {
	void perform() override;
};