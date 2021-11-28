#pragma once 
#include "IEnemyType.h"

class FlyingEnemy : public IEnemyType {
public:
	FlyingEnemy();
	std::string getTypeName() const override;
};