#pragma once
#include "IEnemy.h"
#include "IEnemyBehaviour.h"

class Enemy : public IEnemy {
public:
	Enemy(IEnemyBehaviour* behaviour = nullptr);
	~Enemy();
	static Enemy* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);
	bool init() override;
private:
	
};

