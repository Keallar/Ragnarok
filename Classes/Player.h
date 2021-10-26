#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Player : public Sprite {
public:
	Player* createPlayer();
	bool init();
	void move();
	void jump();

	CREATE_FUNC(Player);
private:
	int speed;
};

