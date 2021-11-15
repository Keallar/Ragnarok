#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>

USING_NS_CC;

class IEnemyType {
public:
	virtual ~IEnemyType() {};
protected:
	std::string filename;
	std::string enemyName;
	b2Filter filter;
	int _hp;
	int _damage;
};