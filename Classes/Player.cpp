#include "Player.h"

USING_NS_CC;

const float Player::ATTACK_COOLDOWN = 0.2f;

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
	hp = 100.f;
	speed = 0.f;
	jumpBegin = 0;
	playerRunState = eRunState::None;
	playerJumpState = eJumpState::None;
	playerAnimState = eAnimState::None;
	attackCooldown = 0;
	jumpBegin = 0;

	return true;
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_D:
		setRunState(eRunState::Right);
		break;
	case EventKeyboard::KeyCode::KEY_A:
		setRunState(eRunState::Left);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (getJumpState() == eJumpState::None) {
			setJumpState(eJumpState::Jump);
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

bool Player::canAttack(float dt) noexcept {
	if (attackCooldown > 0) {
		attackCooldown -= dt;
	}
	else if (attackCooldown <= 0) {
		return true;
	}
	return false;
}

void Player::resetAttackColldown() noexcept {
	attackCooldown = ATTACK_COOLDOWN;
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

void Player::changeHp(float difHp) noexcept {
	if (hp <= 0) {
		return;
	}
	hp -= difHp;
}

float Player::getHp() noexcept {
	return hp;
}