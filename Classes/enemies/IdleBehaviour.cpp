#pragma once
#include "IdleBehaviour.h"
#include "box2d/b2dSprite.h"
#include <random>

void IdleBehaviour::perform(IEnemy* enemy) {
	if (!enemy) {
		CCLOG("ERROR IN IDLE BEHAVIOUR");
		return;
	}
	if (enemy->getType()->getTypeName() == "SimpleEnemy") {
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, 2);
		auto state = dist(rd);
		if (state == static_cast<int>(eIdleState::Sleep)) {

		}
		if (state == static_cast<int>(eIdleState::MoveRight)) {
			//enemy->stopAllActions();
			Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getType()->getMoveRightFrames());
			Animate* moveRightAnim = Animate::create(moveRightAnimation);
			Action* moveRightAct = Repeat::create(moveRightAnim, 1);
			enemy->runAction(moveRightAct);
			enemy->setPositionX(enemy->getPosition().x + 3);
		}
		if (state == static_cast<int>(eIdleState::MoveLeft)) {
			//enemy->stopAllActions();
			Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getType()->getMoveLeftFrames());
			Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
			Action* moveLeftAct = Repeat::create(moveLeftAnim, 1);
			enemy->runAction(moveLeftAct);
			enemy->setPositionX(enemy->getPosition().x - 3);
		}
	}
	if (enemy->getType()->getTypeName() == "FlyingEnemy") {
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, 2);
		auto state = dist(rd);
		if (state == static_cast<int>(eIdleState::Sleep)) {

		}
		if (state == static_cast<int>(eIdleState::MoveRight)) {
			//enemy->stopAllActions();
			Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getType()->getMoveRightFrames());
			Animate* moveRightAnim = Animate::create(moveRightAnimation);
			Action* moveRightAct = Repeat::create(moveRightAnim, 1);
			enemy->runAction(moveRightAct);
			enemy->setPositionX(enemy->getPosition().x + 3);
		}
		if (state == static_cast<int>(eIdleState::MoveLeft)) {
			//enemy->stopAllActions();
			Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getType()->getMoveLeftFrames());
			Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
			Action* moveLeftAct = Repeat::create(moveLeftAnim, 1);
			enemy->runAction(moveLeftAct);
			enemy->setPositionX(enemy->getPosition().x - 3);
		}
	}
}

std::string IdleBehaviour::getBehaviourName() const {
	return "IdleBehaviour";
}
