#include "Player.h"

USING_NS_CC;

Player::Player() {
	init();
}

Player::~Player() {

}

Player* Player::createPlayer() {
	auto playerObj = Player::create("Tur_64.png", Rect(0, 0, 29, 29), b2BodyType::b2_dynamicBody, 0.f, 0);
	return playerObj;
}

Player* Player::create(const std::string& filename, const Rect& rect, b2BodyType type, float32 friction, float32 restitution) {
	Player* sprite = new (std::nothrow) Player();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Player::init() {
	if (!b2Sprite::init()) {
		return false;
	}


	return true;
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
	}
}

void Player::changePos(int delta) {
	//getPhysicsBody()->setVelocity(Vec2(delta, getPhysicsBody()->getVelocity().y));
	getBody()->SetLinearVelocity(b2Vec2(delta, getBody()->GetLinearVelocity().y));
}

void Player::jump() {
	//getPhysicsBody()->setVelocity(getPhysicsBody()->getVelocity() + Vec2(0, jumpSpeed));

	if (getJumpState() == eJumpState::Jump) {
		//getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, PLAYER_JUMP_SPEED));
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

void Player::setRunState(eRunState state) {
	if (state == eRunState::Left && getRunState() == eRunState::Right ||
		state == eRunState::Right && getRunState() == eRunState::Left) {
		playerRunState = eRunState::None;
	}
	else {
		playerRunState = state;
	}
}

void Player::setJumpState(eJumpState state) {
	if (state == eJumpState::Jump) {
		jumpBegin = getPosition().y;
	}
	playerJumpState = state;
}

eRunState Player::getRunState() {
	return playerRunState;
}

eJumpState Player::getJumpState() {
	return playerJumpState;
}