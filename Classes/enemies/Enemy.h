#pragma once
#include "IEnemy.h"
#include "IEnemyBehaviour.h"

class Enemy : public IEnemy {
public:
	Enemy(IEnemyType* type = nullptr, IEnemyBehaviour* behaviour = nullptr);
	~Enemy();
	static Enemy* create(Node* node, Vec2 pos, IEnemyType* type = nullptr, IEnemyBehaviour* behaviour = nullptr);
	bool init() override;
private:
	static int id;
};

