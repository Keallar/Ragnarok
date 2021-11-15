#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class IEnemyBehaviour {
public:
	virtual ~IEnemyBehaviour() {}
	virtual void behaviour() const = 0;
};