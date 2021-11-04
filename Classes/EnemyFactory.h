#pragma once
#include "cocos2d.h"
#include "IEnemy.h"
#include "SimpleEnemy.h"

enum class eEnemyType {
	simpleEnemy,
	boss
};

class EnemyFactory {
public:
	static EnemyFactory* getInstance();
	static SimpleEnemy* createSimpleEnemy();
private:
	static EnemyFactory* instance;
};

