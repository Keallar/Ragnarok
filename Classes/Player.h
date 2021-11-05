#pragma once
#include "ShootingCharacter.h"

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

enum class eAnimState {
	None,
	Run,
	Jump,
	Attack
};

class Player : public ShootingCharacter {
public:
	Player();
	~Player();
	static Player* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);
	static Player* createPlayer();

	virtual bool init();

	void update(float dt) override;

	void setRunState(eRunState state);
	void setJumpState(eJumpState state);
	void setAnimState(eAnimState state);
	eRunState getRunState() noexcept;
	eJumpState getJumpState() noexcept;
	eAnimState getAnimState() noexcept;
	float getHp() noexcept;

	//key callbacks

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void mousePressed(cocos2d::Event* event);

	void move();
	void changePos(int delta);
	void jump();

	//ShootingCharacter function
	void shoot(Vec2 targetPos) override;

	//get from private because they are const & i need bullet speed at scene
	static const int PLAYER_SPEED;
	static const int PLAYER_JUMP_SPEED;
	static const int PLAYER_JUMP_HEIGHT;
	static const int BULLET_SPEED;

	void changeHp(float difHp) noexcept;
private:

	float hp;
	float speed;
	float jumpSpeed;
	int jumpBegin;

	eRunState playerRunState;
	eJumpState playerJumpState;
	eAnimState playerAnimState;

};

