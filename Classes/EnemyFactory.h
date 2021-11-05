#pragma once
#include "cocos2d.h"
#include "IEnemy.h"
#include "SimpleEnemy.h"
#include "box2d/b2dRootWorldNode.h"

enum class eEnemyType {
	simpleEnemy,
	boss
};

class EnemyFactory {
public:
	static EnemyFactory* getInstance();
	static SimpleEnemy* createSimpleEnemy(b2WorldNode* world, Vec2 pos );
private:
	static EnemyFactory* instance;
	static int id;
};

