#pragma once
#include "IEnemy.h"
#include "IEnemyBehaviour.h"

class Enemy : public IEnemy {
public:
	Enemy(IEnemyBehaviour* behaviour = nullptr, IEnemyType* type = nullptr);
	~Enemy();
	static Enemy* create(const std::string& filename, b2BodyType bodyType, float32 friction, float32 restitution, IEnemyBehaviour* behaviour = nullptr, IEnemyType* type = nullptr);
	bool init() override;
private:
	
};

