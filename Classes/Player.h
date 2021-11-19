#pragma once
#include "ShootingCharacter.h"

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

	bool init() override;

	void update(float dt) override;

	void setJumpState(eJumpState state);
	void setAnimState(eAnimState state);
	eJumpState getJumpState() noexcept;
	eAnimState getAnimState() noexcept;
	int getHp() const;
	void setHp(int hp) noexcept;
	void changeHp(float difHp) noexcept;
	int getMana() const;
	void setMana(int mana) noexcept;
	void changeMana(int difMana) noexcept;
	bool isDied() const;
	void setDied(bool state) noexcept;

	//key callbacks
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void mousePressed(cocos2d::Event* event);

	void move(int shift);
	void jump();

	//ShootingCharacter function
	void shoot(cocos2d::Vec2 targetPos, IBulletTypeCreator* bulletCreator) override;

	//get from private because they are const & i need bullet speed at scene
	static const int PLAYER_SPEED;
	static const int PLAYER_JUMP_SPEED;
	static const int PLAYER_JUMP_HEIGHT;
private:
	void changePos(int delta);
	cocos2d::Vec2 clickPosCalculate(cocos2d::EventMouse* mouse);

	int _hp;
	int _mana;
	float _speed;
	float _jumpSpeed;
	int _jumpBegin;
	bool _isDied;

	Bullet* _hook;
	cocos2d::DrawNode* _hookBody;

	eJumpState playerJumpState;
	eAnimState playerAnimState;
};

