#include "Player.h"

USING_NS_CC;
Player* Player::createPlayer() {

	auto ptr = Player::create("test.png", b2BodyType::b2_dynamicBody, 0.0, 0);
	return ptr;
}

Player* Player::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution)
{
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
	case runState::left:
		changePos(-PLAYER_SPEED);
		break;
	case runState::right:
		changePos(PLAYER_SPEED);
		break;
	case runState::none:
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

	if (playerJumpState == jumpState::jump) {
		//getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, PLAYER_JUMP_SPEED));
		getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, PLAYER_JUMP_SPEED));
	}
	if (getPosition().y - jumpBegin >= PLAYER_JUMP_HEIGHT) {
		setJumpState(jumpState::fall);
	}
	if (getJumpState() == jumpState::fall && getBody()->GetLinearVelocity().y == 0) {
		setJumpState(jumpState::none);
		jumpBegin = 0;
	}
}

void Player::setRunState(runState state) {
	if (state == runState::left && playerRunState == runState::right ||
		state == runState::right && playerRunState == runState::left) {
		playerRunState = runState::none;
	}
	else {
		playerRunState = state;
	}
}

void Player::setJumpState(jumpState state) {
	if (state == jumpState::jump) {
		jumpBegin = getPosition().y;
	}
	playerJumpState = state;
}

runState Player::getRunState() {
	return playerRunState;
}

jumpState Player::getJumpState() {
	return playerJumpState;
}