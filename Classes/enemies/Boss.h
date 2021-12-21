#pragma once
#include "IEnemy.h"

class Boss : public IEnemy {
	Boss();
	~Boss() {}
	static Boss* create(Node* node, Vec2 pos, IEnemyBehaviour* behaviour = nullptr);
	bool init();
	virtual void shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) override final;
	virtual void hit() override final;
private:

};
