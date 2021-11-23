#include "IEnemyType.h"

class SimpleEnemy : public IEnemyType {
public:
	SimpleEnemy();
	std::string getTypeName() const override;
};