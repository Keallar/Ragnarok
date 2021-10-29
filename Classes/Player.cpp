#include "Player.h"

USING_NS_CC;

Player::Player() : speed(0), jumpSpeed(0), jumpBegin(0), 
	playerJumpState(eJumpState::None), playerRunState(eRunState::None) {

};

Player::~Player() {

}

Player* Player::createPlayer() {
	auto ptr = Player::create("test.png", b2BodyType::b2_dynamicBody, 0.0, 0);
	return ptr;
}

Player* Player::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	Player* sprite = new (std::nothrow) Player();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Player::move() {
	switch (playerRunState) {
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

	if (playerJumpState == eJumpState::Jump) {
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
	if (state == eRunState::Left && playerRunState == eRunState::Right ||
		state == eRunState::Right && playerRunState == eRunState::Left) {
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