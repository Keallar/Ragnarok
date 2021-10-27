#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

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

class Player : public b2Sprite
{
private:
	runState playerRunState;
	jumpState playerJumpState;
public:
	
	Player() {
		speed = 0;
		jumpSpeed = 0;
		playerJumpState = jumpState::none;
		playerRunState = runState::none;
		jumpBegin = 0;
	};

	~Player() {

	}

	static Player* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);

	void setRunState(runState state);
	void setJumpState(jumpState state);
	runState getRunState();
	jumpState getJumpState();

	int speed;
	float jumpSpeed;
	int jumpBegin;

	static const int PLAYER_SPEED = 20;
	static const int PLAYER_JUMP_SPEED = 20;
	static const int PLAYER_JUMP_HEIGHT = 150;

	static Player* createPlayer();

	void move();
	void changePos(int delta);

	void jump();

	//CREATE_FUNC(Player);
};

