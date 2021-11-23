#include "Player.h"
#include "box2d/b2dRootWorldNode.h"
#include "IShootingPattern.h"

USING_NS_CC;

const int Player::PLAYER_SPEED = 20;
const int Player::PLAYER_JUMP_SPEED = 20;
const int Player::PLAYER_JUMP_HEIGHT = 90;
//const int Player::BULLET_SPEED = 10;

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
	_jumpCount = 0;

	_hook = nullptr;
	_hookBody = DrawNode::create();
	addChild(_hookBody);
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
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		move(-PLAYER_SPEED);
		auto scaleX = getScaleX();
		if (scaleX > 0) {
			scaleX *= -1;
			setScaleX(scaleX);
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		if (getJumpState() == eJumpState::None || _jumpCount != 2) {
			setJumpState(eJumpState::Jump);
			_jumpCount++;
		}
		if (_hook && _hook->isHooked()) {
			_hook->setOnRemove();
			_hook = nullptr;
		}
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		if (getJumpState() == eJumpState::None || _jumpCount != 2) {
			setJumpState(eJumpState::Jump);
			_jumpCount++;
		}
		if (_hook && _hook->isHooked()) {
			_hook->setOnRemove();
			_hook = nullptr;
		}
		break;
	}
	case EventKeyboard::KeyCode::KEY_R:
		if (_hook && _hook->isHooked()) {
			_hook->setOnRemove();
			_hook = nullptr;
		}
		else {
			if (_hook) {
				_hook->setOnRemove();
			}
			shoot(getPosition() + Vec2(45 * getScaleX(), -45), new PlayerHookBulletCreator);
			_hook = dynamic_cast<PlayerHookBullet*>(BulletFactory::getInstance()->getLastBullet());
			break;
		}
		break;
	default:
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
	case EventKeyboard::KeyCode::KEY_R:
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
		if (auto isHook = dynamic_cast<PlayerHookBullet*>(bulletCreator)) {
			dest *= PLAYER_BULLET_SPEED;
		}

		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

Vec2 Player::clickPosCalculate(EventMouse* mouse) {
	auto click = mouse->getLocation();
	setAnimState(eAnimState::Attack);
	auto director = Director::getInstance();
	Vec2 clickPos = Camera::getDefaultCamera()->getPosition() - Vec2{ director->getVisibleSize() / 2 };
	clickPos += click;
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
	if (getPosition().y >= _jumpBegin) {
		setJumpState(eJumpState::Fall);
	}
}

void Player::hookBodyUpdate(float dt) {
	if (_hook && _hook->getLifeTime() > 0) {
		_hookBody->clear();
		Vec2 dest = _hook->getPosition() - getPosition();
		dest.y += getContentSize().width / 2;
		dest.x += getContentSize().height / 2 * getScaleX();
		dest.x *= getScaleX();
		_hookBody->drawLine(Vec2(getContentSize() / 2), dest, Color4F::GRAY);
		if (_hook->isHooked()) {
			//move(0);
			//setJumpState(eJumpState::None);
			dest.normalize();
			dest.x *= getScaleX();
			dest *= 30; //hooked player fly speed
			b2Vec2 playerVel = { dest.x, dest.y };
			getBody()->SetLinearVelocity(playerVel);
		}
	}
	else {
		_hook = nullptr;
		_hookBody->clear();
	}
}

void Player::update(float dt) {	
	hookBodyUpdate(dt);
	shootingCharacterUpdate(dt);
	jump();
}

void Player::setJumpState(eJumpState state) {
	if (state == eJumpState::Jump) {
		_jumpBegin = getPosition().y + PLAYER_JUMP_HEIGHT;
	} 
	if (state == eJumpState::None) {
		_jumpCount = 0;
		_jumpBegin = 0;
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

int Player::getJumpCount() const {
	return _jumpCount;
}