#pragma once
#include "AgressiveBehaviour.h"
#include "IBulletTypeCreator.h"
#include <random>
#define MOVE_COOLDOWN 2.0f;
#define BOSS_MOVE_COOLDOWN 5.f

SimpleAgressiveBehaviour::SimpleAgressiveBehaviour() {
	_stateCooldown = 0;
}

void SimpleAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN SIMPLE AGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		if (_state == static_cast<int>(eAgressiveState::Run)) {
			if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			else if (enemy->getShootTarget().x < enemy->getPositionX() && enemy->getScaleX() < 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			dest.y = 0;
			auto moveAction = MoveBy::create(1.5f, dest);
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.15f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackActionAnim = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

			enemy->runAction(spawn);
		}
		else if (_state == static_cast<int>(eAgressiveState::Jump)) {
			if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			else if (enemy->getShootTarget().x < enemy->getPositionX() && enemy->getScaleX() < 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = JumpBy::create(1.5f, dest, 200, 1);
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.15f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackActionAnim = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

			enemy->runAction(spawn);
		}
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, 1);
		_state = static_cast<int>(dist(rd));
		_stateCooldown = MOVE_COOLDOWN;
	}

	_stateCooldown -= dt;
	enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask(), enemy));
}

std::string SimpleAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveSimple";
}

FlyingAgressiveBehaviour::FlyingAgressiveBehaviour() {
	_stateCooldown = 0;
}

void FlyingAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN FLYING AGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = MoveBy::create(1.5f, dest);
		Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.15f);
		Animate* attackAnim = Animate::create(attackAnimation);
		auto attackActionAnim = Repeat::create(attackAnim, 3);
		Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

		enemy->runAction(spawn);
	}
	_stateCooldown -= dt;
	enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask(), enemy));
}

std::string FlyingAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveFlying";
}

AbobaAgressiveBehaviour::AbobaAgressiveBehaviour() {
	_stateCooldown = 0;
}

void AbobaAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN ABOBA AGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
			auto scale = enemy->getScaleX();
			enemy->setScaleX(-scale);
		}
		else if (enemy->getShootTarget().x < enemy->getPositionX() && enemy->getScaleX() < 0) {
			auto scale = enemy->getScaleX();
			enemy->setScaleX(-scale);
		}
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		dest.y = 0;
		auto moveAction = MoveBy::create(1.5f, dest);
		Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.15f);
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
		CCLOG("ERROR IN WOLF AGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		_stateCooldown = MOVE_COOLDOWN;
		if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
			auto scale = enemy->getScaleX();
			enemy->setScaleX(-scale);
		}
		else if (enemy->getShootTarget().x < enemy->getPositionX() && enemy->getScaleX() < 0) {
			auto scale = enemy->getScaleX();
			enemy->setScaleX(-scale);
		}
		Vec2 pos = enemy->getPosition();
		Vec2 dest = targetPos - pos;
		auto moveAction = JumpBy::create(1.5f, dest, 200, 1);

		enemy->runAction(moveAction);
	}
	_stateCooldown -= dt;
	enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask(), enemy));
}

std::string WolfAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveWolf";
}

BossAgressiveBehaviour::BossAgressiveBehaviour() {
	_stateCooldown = 0;
}

void BossAgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN BOSS AGRESSIVE BEHAVIOUR");
		return;
	}
	if (_stateCooldown <= 0) {
		if (_state == static_cast<int>(eAgressiveState::Run)) {
			if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			else if (enemy->getShootTarget().x < enemy->getPositionX() && enemy->getScaleX() < 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			dest.y = 0;
			auto moveAction = MoveBy::create(1.5f, dest);
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.15f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackActionAnim = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

			enemy->runAction(spawn);
		}
		else if (_state == static_cast<int>(eAgressiveState::Jump)) {
			if (enemy->getShootTarget().x > enemy->getPositionX() && enemy->getScaleX() > 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			else if (enemy->getShootTarget().x < enemy->getPositionX() && enemy->getScaleX() < 0) {
				auto scale = enemy->getScaleX();
				enemy->setScaleX(-scale);
			}
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = JumpBy::create(1.5f, dest, 200, 1);
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.15f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackActionAnim = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackActionAnim);

			enemy->runAction(spawn);
		}
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, 1);
		_state = static_cast<int>(dist(rd));
		_stateCooldown = BOSS_MOVE_COOLDOWN;
	}
	_stateCooldown -= dt;

	enemy->shoot(enemy->getShootTarget(), new FireBulletCreator(enemy->enemyPhysMask(), enemy));
	enemy->hit();
}

std::string BossAgressiveBehaviour::getBehaviourName() const {
	return "AgressiveBoss";
}
