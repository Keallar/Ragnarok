#pragma once
#include "IEnemy.h"
#include "IEnemyBehaviour.h"

class Enemy : public IEnemy {
public:
	Enemy(IEnemyBehaviour* behaviour = nullptr);
	~Enemy();
	static Enemy* create(Node* node, Vec2 pos, std::string type, IEnemyBehaviour* behaviour = nullptr);
	bool init() override;
private:
	static int id;
};

