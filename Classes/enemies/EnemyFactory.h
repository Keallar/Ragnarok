#pragma once
#include "cocos2d.h"
#include "box2d/b2dRootWorldNode.h"
#include "IEnemyBehaviour.h"
#include "IEnemyType.h"
#include "Enemy.h"

enum class eEnemyType {
	simpleEnemy,
	boss
};

class EnemyFactory {
public:
	static EnemyFactory* getInstance();
	static Enemy* createEnemy(b2WorldNode* world, Vec2 pos, IEnemyType* type = nullptr, IEnemyBehaviour* behaviour = nullptr);
private:
	static EnemyFactory* instance;
	static int id;
};

