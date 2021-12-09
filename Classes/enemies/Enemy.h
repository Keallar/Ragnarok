#pragma once
#include "IEnemy.h"
#include "IEnemyBehaviour.h"

class Enemy : public IEnemy {
public:
	Enemy(std::string type, IEnemyBehaviour* behaviour = nullptr);
	~Enemy();
	static Enemy* create(Node* node, Vec2 pos, std::string type, IEnemyBehaviour* behaviour = nullptr);
	bool init(std::string type);
private:
	static int id;
};

