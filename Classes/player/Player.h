#pragma once
#include "ShootingCharacter.h"
#include "PlayerHookBullet.h"
#include "MeleeCharacter.h"
#include "IShootingPattern.h"

enum class eJumpState {
	None,
	Jump,
	Fall
};

enum class eAnimState {
	None,
	Move,
	Jump,
	Fall,
	Attack
};

class Player : public ShootingCharacter, public MeleeCharacter, public b2Sprite {
public:
	Player();
	~Player();
	static Player* create();

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

	float getJumpSpeed();
	//key callbacks
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void mousePressed(cocos2d::Event* event);

	//ShootingCharacter function
	void shoot(cocos2d::Vec2 targetPos, IBulletTypeCreator* bulletCreator) override;

	//melee Func
	void hit() override;
	void cleanHit() override;
	void meleeInit() override;
	void meleeUpdate(float dt);

	//functions for testing
	int getJumpCount() const;

	//for change bullets
	void changeBulletCreator(IBulletTypeCreator* bulletCreator);
private:
	//shoot
	IBulletTypeCreator* _bulletCreator;
	IdleShootingPattern* _hookPattern;

	//functions
	void move(float dt);
	void jump(float dt);
	void hookBodyUpdate(float dt);
	cocos2d::Vec2 clickPosCalculate(cocos2d::EventMouse* mouse);
	//init files
	std::string _fileName;
	std::string _idleAnimFile;
	std::string _attackAnimFile;
	std::string _jumpAnimFile;
	std::string _fallAnimFile;
	std::string _moveAnimFile;
	//params
	int _hp;
	int _mana;
	float _curSpeed;
	float _speed;
	float _maxSpeed;
	float _jumpSpeed;
	int _jumpBegin;
	bool _isDied;
	int _jumpCount;
	static const int JUMP_HEIGHT;

	PlayerHookBullet* _hook;
	cocos2d::DrawNode* _hookBody;
	b2RopeJoint* _hookJuint;

	eJumpState _playerJumpState;
	eAnimState _playerAnimState;

	cocos2d::Vector<SpriteFrame*> _idleAnimFrames;
	cocos2d::Vector<SpriteFrame*> _attackAnimFrames;
	cocos2d::Vector<SpriteFrame*> _jumpAnimFrames;
	cocos2d::Vector<SpriteFrame*> _fallAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveAnimFrames;
};

