#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

enum class eRunState {
	None,
	Left,
	Right
};

enum class eJumpState {
	None,
	Jump,
	Fall
};

class Player : public b2Sprite
{
public:
	Player();
	~Player();
	static Player* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);
	static Player* createPlayer();

	virtual bool init();

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setRunState(eRunState state);
	void setJumpState(eJumpState state);
	eRunState getRunState();
	eJumpState getJumpState();

	void move();
	void changePos(int delta);
	void jump();

	//CREATE_FUNC(Player);
private:
	static const int PLAYER_SPEED = 20;
	static const int PLAYER_JUMP_SPEED = 20;
	static const int PLAYER_JUMP_HEIGHT = 150;

	int speed;
	float jumpSpeed;
	int jumpBegin;

	eRunState playerRunState;
	eJumpState playerJumpState;
};

