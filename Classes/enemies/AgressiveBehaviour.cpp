#pragma once
#include "AgressiveBehaviour.h"
#include "IBulletTypeCreator.h"
#define MOVE_COOLDOWN 2.f;

SimpleAgressiveBehaviour::SimpleAgressiveBehaviour() {
	_stateCooldown = 0;
}

void SimpleAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN SIMPLEAGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = MoveBy::create(1.5f, dest);
		Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
		Animate* attackAnim = Animate::create(attackAnimation);
		auto attackActionAnim = Repeat::create(attackAnim, 3);
		Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

		enemy->runAction(spawn);
	}
	_stateCooldown -= dt;
	enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask()));
}

std::string SimpleAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveSimple";
}

FlyingAgressiveBehaviour::FlyingAgressiveBehaviour() {
	_stateCooldown = 0;
}

void FlyingAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN FLYINGAGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = MoveBy::create(1.5f, dest);
		Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
		Animate* attackAnim = Animate::create(attackAnimation);
		auto attackActionAnim = Repeat::create(attackAnim, 3);
		Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

		enemy->runAction(spawn);
	}
	_stateCooldown -= dt;
	enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask()));
}

std::string FlyingAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveFlying";
}

AbobaAgressiveBehaviour::AbobaAgressiveBehaviour() {
	_stateCooldown = 0;
}

void AbobaAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN ABOBAAGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
			auto scale = enemy->getScaleX();
			enemy->setScaleX(-scale);
		}
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = MoveBy::create(1.5f, dest);
		Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
		Animate* attackAnim = Animate::create(attackAnimation);
		auto attackActionAnim = Repeat::create(attackAnim, 3);
		Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

		enemy->runAction(spawn);
	}
	_stateCooldown -= dt;
	enemy->hit();
}

std::string AbobaAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveAboba";
}

WolfAgressiveBehaviour::WolfAgressiveBehaviour() {
	_stateCooldown = 0;
}

void WolfAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN WOLFAGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = JumpBy::create(1.5f, dest, 200, 1);

		enemy->runAction(moveAction);
	}
	_stateCooldown -= dt;
	enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask()));
}

std::string WolfAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveWolf";
}

BossAgressiveBehaviour::BossAgressiveBehaviour() {
	_stateCooldown = 0;
}

void BossAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN BOSSAGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = MoveBy::create(1.5f, dest);
		Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
		Animate* attackAnim = Animate::create(attackAnimation);
		auto attackActionAnim = Repeat::create(attackAnim, 3);
		Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

		enemy->runAction(spawn);
	}
	_stateCooldown -= dt;
}

std::string BossAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveBoss";
}
