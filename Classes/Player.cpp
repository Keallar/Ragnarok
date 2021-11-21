#include "Player.h"
#include "box2d/b2dRootWorldNode.h"
#include "IShootingPattern.h"

USING_NS_CC;

const int Player::PLAYER_SPEED = 20;
const int Player::PLAYER_JUMP_SPEED = 20;
const int Player::PLAYER_JUMP_HEIGHT = 90;
const int Player::BULLET_SPEED = 10;

Player::Player() {
	init();
}

Player::~Player() {
}

Player* Player::createPlayer() {
	auto playerObj = Player::create("Tur_64.png", b2BodyType::b2_dynamicBody, 0.f, 0);
	return playerObj;
}

Player* Player::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	Player* sprite = new (std::nothrow) Player();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->initBody(type, friction, restitution);
		//sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Player::init() {
	if (!b2Sprite::init()) {
		return false;
	}
	_shootingPattern = new IdleShootingPattern(this);
	_attackCooldown = 0;
	_hp = 100;
	_mana = 100;
	_speed = 0.f;
	_jumpBegin = 0;
	playerJumpState = eJumpState::None;
	playerAnimState = eAnimState::None;
	_isDied = false;

	return true;
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_D:
	{
		move(PLAYER_SPEED);
		auto scaleX = getScaleX();
		if (scaleX < 0) {
			scaleX *= -1;
			setScaleX(scaleX);
		}
	}
	break;
	case EventKeyboard::KeyCode::KEY_A:
	{
		move(-PLAYER_SPEED);
		auto scaleX = getScaleX();
		if (scaleX > 0) {
			scaleX *= -1;
			setScaleX(scaleX);
		}
	}
	break;
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		if (getJumpState() == eJumpState::None) {
			setJumpState(eJumpState::Jump);
		}
		else if (getJumpState() == eJumpState::Fall /*|| getJumpState() == eJumpState::Jump*/) {
			setJumpState(eJumpState::DoubleJump);
		}
	}
	break;
	case EventKeyboard::KeyCode::KEY_W:
	{
		if (getJumpState() == eJumpState::None) {
			setJumpState(eJumpState::Jump);
		}
		else if (getJumpState() == eJumpState::Fall /*|| getJumpState() == eJumpState::Jump*/) {
			setJumpState(eJumpState::DoubleJump);
		}
	}
	break;
	}
}

void Player::KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_A:
		move(0);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		move(0);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		setJumpState(eJumpState::Fall);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		setJumpState(eJumpState::Fall);
		break;
	default:
		break;
	}
}

void Player::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {

		if (auto isIdle = dynamic_cast<PlayerIdleBulletCreator*>(bulletCreator)) {
			_attackCooldown = PLAYER_ATTACK_COOLDOWN;
		}
		else if (auto isBig = dynamic_cast<PlayerBigBulletCreator*>(bulletCreator)) {
			_attackCooldown = PLAYER_BIG_ATTACK_COOLDOWN;
		}
		Vec2 pos = getPosition();
		Vec2 dest = targetPos - pos;
		dest.normalize();
		dest.y *= -1;
		dest *= PLAYER_BULLET_SPEED;

		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

Vec2 Player::clickPosCalculate(EventMouse* mouse) {
	auto click = mouse->getLocation();
	setAnimState(eAnimState::Attack);
	auto director = Director::getInstance();
	Vec2 clickPos = Camera::getDefaultCamera()->getPosition() - Vec2{ director->getVisibleSize() / 2 };
	clickPos += click;
	//clickPos.y = Director::getInstance()->getVisibleSize().height - click.y + Director::getInstance()->getVisibleOrigin().y;
	//clickPos = Vec2(Director::getInstance()->getVisibleSize()) - click + Director::getInstance()->getVisibleOrigin();
	return clickPos;
}

void Player::mousePressed(cocos2d::Event* event) {
	EventMouse* mouse = dynamic_cast<EventMouse*>(event);

	if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
		shoot(clickPosCalculate(mouse), new PlayerIdleBulletCreator);
	}
	else if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
		shoot(clickPosCalculate(mouse), new PlayerBigBulletCreator);
	}
}

void Player::move(int shift) {
	changePos(shift);
}

void Player::changePos(int delta) {
	getBody()->SetLinearVelocity(b2Vec2(delta, getBody()->GetLinearVelocity().y));
}

void Player::jump() {
	if (getJumpState() == eJumpState::Jump) {
		getBody()->ApplyLinearImpulseToCenter({ 0, 10 }, true);
	}
	if (getPosition().y - _jumpBegin >= PLAYER_JUMP_HEIGHT) {
		setJumpState(eJumpState::Fall);
	}
	if (getJumpState() == eJumpState::Fall && getBody()->GetLinearVelocity().y <= 1 && getBody()->GetLinearVelocity().y >= -1) {
		setJumpState(eJumpState::None);
		_jumpBegin = 0;
	}
	if (getJumpState() == eJumpState::DoubleJump) {
		//getBody()->SetLinearVelocity({ 0, 10 });
		getBody()->ApplyLinearImpulseToCenter({ 0, 10 }, true);
	}
}

void Player::update(float dt) {	
	shootingCharacterUpdate(dt);
	jump();
}

void Player::setJumpState(eJumpState state) {
	if (getJumpState() == eJumpState::None) {
		_jumpBegin = getPosition().y;
	} 
	else if (getJumpState() == eJumpState::DoubleJump) {
		_jumpBegin += getPosition().y;
	}
	playerJumpState = state;
}

void Player::setAnimState(eAnimState state) {
	playerAnimState = state;
}

eAnimState Player::getAnimState() noexcept {
	return playerAnimState;
}

eJumpState Player::getJumpState() noexcept {
	return playerJumpState;
}

int Player::getMana() const {
	return _mana;
}

void Player::setMana(int mana) noexcept {
	_mana = mana;
}

void Player::changeMana(int difMana) noexcept {
	if (_mana <= 0) {
		return;
	}
	_mana -= difMana;
}

int Player::getHp() const {
	return _hp;
}

void Player::setHp(int hp) noexcept {
	_hp = hp;
}

void Player::changeHp(float difHp) noexcept {
	if (_hp <= 0) {
		_isDied = true;
		return;
	}
	_hp += difHp;
}

bool Player::isDied() const {
	return _isDied;
}

void Player::setDied(bool state) noexcept {
	_isDied = state;
}