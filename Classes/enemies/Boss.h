#pragma once
#include "IEnemy.h"

class Boss : public IEnemy {
public:
	Boss();
	~Boss() {}
	static Boss* create(Node* node, Vec2 pos, IEnemyBehaviour* behaviour = nullptr);
	bool init();
	virtual void shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) override final;
	virtual void meleeInit() override final;
	virtual void hit() override final;
private:

};
