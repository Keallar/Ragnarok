#include "Player.h"

USING_NS_CC;
Player* Player::createPlayer() {
	Player* ptr = Player::create();
	ptr->setTexture("helloWorld.png");
	ptr->speed = 0;
	ptr->jumpSpeed = 0;
	ptr->setRunState(runState::none);
	ptr->setJumpState(jumpState::none);
	auto physicsBody = PhysicsBody::createBox(ptr->getContentSize(), PhysicsMaterial(0, 0, 0));
	ptr->setPhysicsBody(physicsBody);
	ptr->getPhysicsBody()->setRotationEnable(false);
	return ptr;
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
	getPhysicsBody()->setVelocity(Vec2(delta, getPhysicsBody()->getVelocity().y));
}

void Player::jump() {
	//getPhysicsBody()->setVelocity(getPhysicsBody()->getVelocity() + Vec2(0, jumpSpeed));

	if (playerJumpState == jumpState::jump) {
		getPhysicsBody()->setVelocity(Vec2(getPhysicsBody()->getVelocity().x, PLAYER_JUMP_SPEED));
	}
	if (getPosition().y - jumpBegin >= PLAYER_JUMP_HEIGHT) {
		setJumpState(jumpState::fall);
	}
	if (getJumpState() == jumpState::fall && getPhysicsBody()->getVelocity().y == 0) {
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