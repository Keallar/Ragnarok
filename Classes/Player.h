#pragma once
#include "cocos2d.h"

enum class runState {
	left,
	none,
	right
};

enum class jumpState {
	jump,
	fall,
	none
};

class Player : public cocos2d::Sprite
{
private:
	runState playerRunState;
	jumpState playerJumpState;
public:

	void setRunState(runState state);
	void setJumpState(jumpState state);
	runState getRunState();
	jumpState getJumpState();

	int speed;
	float jumpSpeed;
	int jumpBegin;

	static const int PLAYER_SPEED = 200;
	static const int PLAYER_JUMP_SPEED = 200;
	static const int PLAYER_JUMP_HEIGHT = 150;

	static Player* createPlayer();

	void move();
	void changePos(int delta);

	void jump();

	CREATE_FUNC(Player);
};

