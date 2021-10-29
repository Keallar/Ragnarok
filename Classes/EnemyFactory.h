#pragma once
#include "cocos2d.h"
#include "IEnemy.h"
#include "SimpleEnemy.h"

class EnemyFactory {
public:
	static EnemyFactory* getInstance();
	static SimpleEnemy* createSimpleEnemy();
private:
	EnemyFactory();
	~EnemyFactory() {};
	static EnemyFactory* instance;
};

