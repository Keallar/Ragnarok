#pragma once
#include "IdleBehaviour.h"
#include "box2d/b2dSprite.h"
#include <random>
#define STATE_COOLDOWN 3.f

std::random_device rd;

SimpleIdleBehaviour::SimpleIdleBehaviour() {
	_stateCooldown = 0;
	_state = 0;
}

void SimpleIdleBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN SIMPLE IDLE BEHAVIOUR");
		return;
	}
	else {
		if (_stateCooldown <= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				enemy->stopAllActions();
				Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
				Animate* idleAnim = Animate::create(idleAnimation);
				Action* idleAction = RepeatForever::create(idleAnim);

				enemy->runAction(idleAction);
			}
			else if (_state == static_cast<int>(eIdleState::MoveRight)) {
				enemy->stopAllActions();
				Vec2 dest = { 150, 0 };
				auto moveRightAct = MoveBy::create(2.0f, dest);
				Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveRightAnim = Animate::create(moveRightAnimation);
				auto moveRightActAnim = RepeatForever::create(moveRightAnim);

				auto spawn = Spawn::createWithTwoActions(moveRightActAnim, moveRightAct);

				enemy->runAction(spawn);
			}
			else if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				enemy->stopAllActions();
				Vec2 dest = { -150, 0 };
				auto moveLeftAct = MoveBy::create(2.0f, dest);
				Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
				auto moveLeftActAnim = RepeatForever::create(moveLeftAnim);

				auto spawn = Spawn::createWithTwoActions(moveLeftActAnim, moveLeftAct);

				enemy->runAction(spawn);
			}
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
	}
	_stateCooldown -= dt;
}

std::string SimpleIdleBehaviour::getBehaviourName() const {
	return "IdleSimple";
}

//////////////////////////////////////////////////////////////////////////////////////////

FlyingIdleBehaviour::FlyingIdleBehaviour() {
	_stateCooldown = 0;
	_state = 0;
}

void FlyingIdleBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN FLYING IDLE BEHAVIOUR");
		return;
	}
	else {
		if (_stateCooldown <= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				enemy->stopAllActions();
				Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
				Animate* idleAnim = Animate::create(idleAnimation);
				Action* idleAction = RepeatForever::create(idleAnim);

				enemy->runAction(idleAction);
			}
			else if (_state == static_cast<int>(eIdleState::MoveRight)) {
				enemy->stopAllActions();
				Vec2 dest = { 150, 0 };
				auto moveRightAct = MoveBy::create(2.0f, dest);
				Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveRightAnim = Animate::create(moveRightAnimation);
				auto moveRightActAnim = RepeatForever::create(moveRightAnim);

				auto spawn = Spawn::createWithTwoActions(moveRightActAnim, moveRightAct);

				enemy->runAction(spawn);
			}
			else if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				enemy->stopAllActions();
				Vec2 dest = { -150, 0 };
				auto moveLeftAct = MoveBy::create(2.0f, dest);
				Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
				auto moveLeftActAnim = RepeatForever::create(moveLeftAnim);

				auto spawn = Spawn::createWithTwoActions(moveLeftActAnim, moveLeftAct);

				enemy->runAction(spawn);
			}
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
	}
	_stateCooldown -= dt;
}


std::string FlyingIdleBehaviour::getBehaviourName() const {
	return "IdleFlying";
}

//////////////////////////////////////////////////////////////////////////////////////////

AbobaIdleBehaviour::AbobaIdleBehaviour() {
	_stateCooldown = 0;
	_state = 0;
}

void AbobaIdleBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN ABOBA IDLE BEHAVIOUR");
		return;
	}
	else {
		if (_stateCooldown <= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				enemy->stopAllActions();
				Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
				Animate* idleAnim = Animate::create(idleAnimation);
				Action* idleAction = RepeatForever::create(idleAnim);

				enemy->runAction(idleAction);
			}
			else if (_state == static_cast<int>(eIdleState::MoveRight)) {
				enemy->stopAllActions();
				Vec2 dest = { 150, 0 };
				auto moveRightAct = MoveBy::create(2.0f, dest);
				Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveRightAnim = Animate::create(moveRightAnimation);
				auto moveRightActAnim = RepeatForever::create(moveRightAnim);

				auto spawn = Spawn::createWithTwoActions(moveRightActAnim, moveRightAct);

				enemy->runAction(spawn);
			}
			else if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				enemy->stopAllActions();
				Vec2 dest = { -150, 0 };
				auto moveLeftAct = MoveBy::create(2.0f, dest);
				Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
				auto moveLeftActAnim = RepeatForever::create(moveLeftAnim);

				auto spawn = Spawn::createWithTwoActions(moveLeftActAnim, moveLeftAct);

				enemy->runAction(spawn);
			}
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
	}
	_stateCooldown -= dt;
}

std::string AbobaIdleBehaviour::getBehaviourName() const {
	return "IdleAboba";
}

//////////////////////////////////////////////////////////////////////////////////////////

WolfIdleBehaviour::WolfIdleBehaviour() {
	_stateCooldown = 0;
	_state = 0;
}

void WolfIdleBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN WOLF IDLE BEHAVIOUR");
		return;
	}
	else {
		if (_stateCooldown <= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				enemy->stopAllActions();
				Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
				Animate* idleAnim = Animate::create(idleAnimation);
				Action* idleAction = RepeatForever::create(idleAnim);

				enemy->runAction(idleAction);
			}
			else if (_state == static_cast<int>(eIdleState::MoveRight)) {
				enemy->stopAllActions();
				Vec2 dest = { 150, 0 };
				auto moveRightAct = MoveBy::create(2.0f, dest);
				Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveRightAnim = Animate::create(moveRightAnimation);
				auto moveRightActAnim = RepeatForever::create(moveRightAnim);

				auto spawn = Spawn::createWithTwoActions(moveRightActAnim, moveRightAct);

				enemy->runAction(spawn);
			}
			else if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				enemy->stopAllActions();
				Vec2 dest = { -150, 0 };
				auto moveLeftAct = MoveBy::create(2.0f, dest);
				Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
				auto moveLeftActAnim = RepeatForever::create(moveLeftAnim);

				auto spawn = Spawn::createWithTwoActions(moveLeftActAnim, moveLeftAct);

				enemy->runAction(spawn);
			}
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
	}
	_stateCooldown -= dt;
}

std::string WolfIdleBehaviour::getBehaviourName() const {
	return "WolfIdle";
}

//////////////////////////////////////////////////////////////////////////////////////////

BossIdleBehaviour::BossIdleBehaviour() {
	_stateCooldown = STATE_COOLDOWN;
	_state = 0;
}

void BossIdleBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN BOSS IDLE BEHAVIOUR");
		return;
	}
	else {
		if (_stateCooldown <= 0) {
			if (_state == static_cast<int>(eIdleState::Sleep)) {
				enemy->stopAllActions();
				Animation* idleAnimation = Animation::createWithSpriteFrames(enemy->getIdleFrames(), 0.13f);
				Animate* idleAnim = Animate::create(idleAnimation);
				Action* idleAction = RepeatForever::create(idleAnim);

				enemy->runAction(idleAction);
			}
			else if (_state == static_cast<int>(eIdleState::MoveRight)) {
				enemy->stopAllActions();
				Vec2 dest = { 150, 0 };
				auto moveRightAct = MoveBy::create(2.0f, dest);
				Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveRightAnim = Animate::create(moveRightAnimation);
				auto moveRightActAnim = RepeatForever::create(moveRightAnim);

				auto spawn = Spawn::createWithTwoActions(moveRightActAnim, moveRightAct);

				enemy->runAction(spawn);
			}
			else if (_state == static_cast<int>(eIdleState::MoveLeft)) {
				enemy->stopAllActions();
				Vec2 dest = { -150, 0 };
				auto moveLeftAct = MoveBy::create(2.0f, dest);
				Animation* moveLeftAnimation = Animation::createWithSpriteFrames(enemy->getMoveFrames(), 0.13f);
				Animate* moveLeftAnim = Animate::create(moveLeftAnimation);
				auto moveLeftActAnim = RepeatForever::create(moveLeftAnim);

				auto spawn = Spawn::createWithTwoActions(moveLeftActAnim, moveLeftAct);

				enemy->runAction(spawn);
			}
			std::random_device rd;
			std::uniform_int_distribution<int> dist(0, 2);
			_state = static_cast<int>(dist(rd));
			_stateCooldown = STATE_COOLDOWN;
		}
	}
	_stateCooldown -= dt;
}

std::string BossIdleBehaviour::getBehaviourName() const {
	return "IdleBoss";
}
