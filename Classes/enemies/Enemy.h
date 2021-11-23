#pragma once
#include "IEnemy.h"
#include "IEnemyBehaviour.h"

class Enemy : public IEnemy {
public:
	Enemy(IEnemyType* type = nullptr, IEnemyBehaviour* behaviour = nullptr);
	~Enemy();
	static Enemy* create(b2BodyType bodyType, float32 friction, float32 restitution, IEnemyType* type = nullptr, IEnemyBehaviour* behaviour = nullptr);
	bool init() override;
private:
	
};

