#pragma once
#include "IdleBehaviour.h"
#include "box2d/b2dSprite.h"
#include <random>
#define STATE_COOLDOWN 2.f

std::random_device rd;

IdleBehaviour::IdleBehaviour() {
	_stateCooldown = STATE_COOLDOWN;
	_state = 0;
}

void IdleBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN IDLE BEHAVIOUR");
		return;
	}
	else if (enemy->getName().substr(0, 6) == "Simple") {
		std::uniform_int_distribution<int> dist(0, 2);
		auto state = dist(rd);
		if (state == static_cast<int>(eIdleState::Sleep)) {
			if (!enemy->getActionByTag(0)) {
				Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
				Animate* idleAnim = Animate::create(idleAnimation);
				Action* idleAction = Repeat::create(idleAnim, 1);
				idleAction->setTag(0);
				enemy->runAction(idleAction);
			}
		}
		if (state == static_cast<int>(eIdleState::MoveRight)) {
			if (!enemy->getActionByTag(1)) {
				Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveRightFrames(), 0.13f);
				Animate* moveRightAnim = Animate::create(moveRightAnimation);
				Action* moveRightAct = Repeat::create(moveRightAnim, 1);
				moveRightAct->setTag(1);
				enemy->runAction(moveRightAct);
			}
			enemy->setPositionX(enemy->getPosition().x + 3);
		}
		if (state == static_cast<int>(eIdleState::MoveLeft)) {
			if (!enemy->getActionByTag(2)) {
				Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveLeftFrames(), 0.13f);
				Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
				Action* moveLeftAct = Repeat::create(moveLeftAnim, 1);
				moveLeftAct->setTag(2);
				enemy->runAction(moveLeftAct);
			}
			enemy->setPositionX(enemy->getPosition().x - 3);
		}
	}
	else if (enemy->getName().substr(0, 6) == "Flying") {
		if (_stateCooldown <= 0) {
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
		if (_stateCooldown >= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				if (!enemy->getActionByTag(0)) {
					Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
					Animate* idleAnim = Animate::create(idleAnimation);
					Action* idleAction = Repeat::create(idleAnim, 1);
					idleAction->setTag(0);
					enemy->runAction(idleAction);
				}
			}
			if (_state == static_cast<int>(eIdleState::MoveRight)) {
				if (!enemy->getActionByTag(1)) {
					Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveRightFrames(), 0.13f);
					Animate* moveRightAnim = Animate::create(moveRightAnimation);
					Action* moveRightAct = Repeat::create(moveRightAnim, 1);
					moveRightAct->setTag(1);
					enemy->runAction(moveRightAct);
				}
				enemy->setPositionX(enemy->getPosition().x + 3);
			}
			if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				if (!enemy->getActionByTag(2)) {
					Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveLeftFrames(), 0.13f);
					Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
					Action* moveLeftAct = Repeat::create(moveLeftAnim, 1);
					moveLeftAct->setTag(2);
					enemy->runAction(moveLeftAct);
				}
				enemy->setPositionX(enemy->getPosition().x - 3);
			}
		}
	}
	else if (enemy->getName().substr(0, 5) == "Aboba") {
		if (_stateCooldown <= 0) {
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
		if (_stateCooldown >= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				if (!enemy->getActionByTag(0)) {
					Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
					Animate* idleAnim = Animate::create(idleAnimation);
					Action* idleAction = Repeat::create(idleAnim, 1);
					idleAction->setTag(0);
					enemy->runAction(idleAction);
				}
			}
			if (_state == static_cast<int>(eIdleState::MoveRight)) {
				if (!enemy->getActionByTag(1)) {
					Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveRightFrames(), 0.13f);
					Animate* moveRightAnim = Animate::create(moveRightAnimation);
					Action* moveRightAct = Repeat::create(moveRightAnim, 1);
					moveRightAct->setTag(1);
					enemy->runAction(moveRightAct);
				}
				enemy->setPositionX(enemy->getPosition().x + 3);
			}
			if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				if (!enemy->getActionByTag(2)) {
					Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveLeftFrames(), 0.13f);
					Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
					Action* moveLeftAct = Repeat::create(moveLeftAnim, 1);
					moveLeftAct->setTag(2);
					enemy->runAction(moveLeftAct);
				}
				enemy->setPositionX(enemy->getPosition().x - 3);
			}
		}
	}
	else if (enemy->getName().substr(0, 4) == "Wolf") {
		if (_stateCooldown <= 0) {
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
		if (_stateCooldown >= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				if (!enemy->getActionByTag(0)) {
					Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
					Animate* idleAnim = Animate::create(idleAnimation);
					Action* idleAction = Repeat::create(idleAnim, 1);
					idleAction->setTag(0);
					enemy->runAction(idleAction);
				}
			}
			if (_state == static_cast<int>(eIdleState::MoveRight)) {
				if (!enemy->getActionByTag(1)) {
					Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveRightFrames(), 0.13f);
					Animate* moveRightAnim = Animate::create(moveRightAnimation);
					Action* moveRightAct = Repeat::create(moveRightAnim, 1);
					moveRightAct->setTag(1);
					enemy->runAction(moveRightAct);
				}
				enemy->setPositionX(enemy->getPosition().x + 3);
			}
			if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				if (!enemy->getActionByTag(2)) {
					Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveLeftFrames(), 0.13f);
					Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
					Action* moveLeftAct = Repeat::create(moveLeftAnim, 1);
					moveLeftAct->setTag(2);
					enemy->runAction(moveLeftAct);
				}
				enemy->setPositionX(enemy->getPosition().x - 3);
			}
		}
	}
	_stateCooldown -= dt;
}

std::string IdleBehaviour::getBehaviourName() const {
	return "Idle";
}
