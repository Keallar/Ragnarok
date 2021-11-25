#pragma once 
#include "IEnemyType.h"
#include <vector>

class FlyingEnemy : public IEnemyType {
public:
	FlyingEnemy();
	std::string getTypeName() const override;
};