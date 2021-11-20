#pragma once
#include "IEnemy.h"

class IEnemyBehaviour {
public:
	virtual ~IEnemyBehaviour() {}
	virtual void perform(IEnemy* enemy) = 0;
};
