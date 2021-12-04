#pragma once 
#include "IEnemyType.h"

class AbobaEnemy : public IEnemyType {
public:
	AbobaEnemy();
	std::string getTypeName() const override;
};