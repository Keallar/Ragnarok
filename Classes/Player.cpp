#include "Player.h"
#include "box2d/b2dRootWorldNode.h"

USING_NS_CC;

const int Player::PLAYER_SPEED = 20;
const int Player::PLAYER_JUMP_SPEED = 20;
const int Player::PLAYER_JUMP_HEIGHT = 70;
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
	attackCooldown = 0;
	_hp = 100;
	_mana = 100;
	_speed = 0.f;
	jumpBegin = 0;
	playerRunState = eRunState::None;
	playerJumpState = eJumpState::None;
	playerAnimState = eAnimState::None;
	jumpBegin = 0;

	return true;
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_D:
	{
		setRunState(eRunState::Right);
		auto scaleX = getScaleX();
		if (scaleX < 0) {
			scaleX *= -1;
			setScaleX(scaleX);
		}
	}
	break;
	case EventKeyboard::KeyCode::KEY_A:
	{
		setRunState(eRunState::Left);
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
	}
	break;
	}
}

void Player::KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_D:
		setRunState(eRunState::Left);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		setRunState(eRunState::Right);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		setJumpState(eJumpState::Fall);
		break;
	default:
		break;
	}
}

void Player::shoot(Vec2 targetPos) {
	if (attackCooldown <= 0) {
		attackCooldown = PLAYER_ATTACK_COOLDOWN;
		Vec2 pos = getPosition();
		
		Vec2 dest = targetPos - pos;
		dest.normalize();
		dest *= BULLET_SPEED;

		CreateBulletOnParent(eBulletType::playerOrdinary, pos, dest);
	}
}

void Player::mousePressed(cocos2d::Event* event) {
	EventMouse* mouse = dynamic_cast<EventMouse*>(event);

	if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

		auto click = mouse->getLocation();
		setAnimState(eAnimState::Attack);
		auto director = Director::getInstance();
		Vec2 clickPos = Camera::getDefaultCamera()->getPosition() - Vec2{ director->getVisibleSize() / 2 };
		clickPos += click;
		clickPos.y = Director::getInstance()->getVisibleSize().height - click.y + Director::getInstance()->getVisibleOrigin().y;

		shoot(clickPos);
	}
}

void Player::move() {
	switch (getRunState()) {
	case eRunState::Left:
		changePos(-PLAYER_SPEED);
		break;
	case eRunState::Right:
		changePos(PLAYER_SPEED);
		break;
	case eRunState::None:
		changePos(0);
		break;
	default:
		break;
	}
}

void Player::changePos(int delta) {
	getBody()->SetLinearVelocity(b2Vec2(delta, getBody()->GetLinearVelocity().y));
}

void Player::jump() {

	if (getJumpState() == eJumpState::Jump) {
		getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, PLAYER_JUMP_SPEED));
	}
	if (getPosition().y - jumpBegin >= PLAYER_JUMP_HEIGHT) {
		setJumpState(eJumpState::Fall);
	}
	if (getJumpState() == eJumpState::Fall && getBody()->GetLinearVelocity().y <= 1 && getBody()->GetLinearVelocity().y >= -1) {
		setJumpState(eJumpState::None);
		jumpBegin = 0;
	}
}

void Player::update(float dt) {	
	ShootingCharacterUpdate(dt);
	move();
	jump();
}

void Player::setRunState(eRunState state) {
	if (state == eRunState::Left && getRunState() == eRunState::Right ||
		state == eRunState::Right && getRunState() == eRunState::Left) {
		playerRunState = eRunState::None;
		return;
	}
	playerRunState = state;
}

void Player::setJumpState(eJumpState state) {
	if (state == eJumpState::Jump) {
		jumpBegin = getPosition().y;
	}
	playerJumpState = state;
}

void Player::setAnimState(eAnimState state) {
	playerAnimState = state;
}

eRunState Player::getRunState() noexcept {
	return playerRunState;
}

eAnimState Player::getAnimState() noexcept {
	return playerAnimState;
}

eJumpState Player::getJumpState() noexcept {
	return playerJumpState;
}

int Player::getMana() noexcept {
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

int Player::getHp() noexcept {
	return _hp;
}

void Player::setHp(int hp) noexcept {
	_hp = hp;
}

void Player::changeHp(float difHp) noexcept {
	if (_hp <= 0) {
		return;
	}
	_hp += difHp;
}