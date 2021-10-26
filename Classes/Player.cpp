#include "Player.h"

USING_NS_CC;
Player* Player::createPlayer() {
	Player* playerObj =  Player::create();
	playerObj->setTexture("HelloWorld.png");
	return playerObj;
}

bool Player::init() {
	/*if (!createPlayer()) {
		return false;
	}*/
	return true;
}

void Player::move() {

}

void Player::jump() {

}