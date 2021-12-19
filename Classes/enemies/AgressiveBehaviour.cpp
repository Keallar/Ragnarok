#pragma once
#include "AgressiveBehaviour.h"
#include "IBulletTypeCreator.h"
#include "ShootingCharacter.h"
#include "MeleeCharacter.h"

constexpr auto MOVE_COOLDOWN = 2.f;

AgressiveBehaviour::AgressiveBehaviour() {
	_moveCooldown = 2.f;
}

void AgressiveBehaviour::perform(IEnemy* enemy, Vec2 targetPos, float dt) {
	if (!enemy) {
		CCLOG("ERROR IN IDLE BEHAVIOUR");
		return;
	}
	if (enemy->getName().substr(0, 6) == "Simple") {
		if (_moveCooldown <= 0) {
			_moveCooldown = MOVE_COOLDOWN;
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = MoveBy::create(1.5f, dest);
			//TODO Create different directions of moving 
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackAction = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackAction);
			
			enemy->runAction(spawn);
		}
		_moveCooldown -= dt;
	}
	if (enemy->getName().substr(0, 6) == "Flying") {
		if (_moveCooldown <= 0) {
			_moveCooldown = MOVE_COOLDOWN;
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = MoveBy::create(1.5f, dest);
			//TODO Create different directions of moving 
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackAction = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackAction);

			enemy->runAction(spawn);
		}
		_moveCooldown -= dt;
		enemy->shoot(enemy->getShootTarget(), new IdleBulletCreator(enemy->enemyPhysMask()));
	}
	if (enemy->getName().substr(0, 5) == "Aboba") {
		if (_moveCooldown <= 0) {
			_moveCooldown = MOVE_COOLDOWN;
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = MoveBy::create(1.5f, dest);
			//TODO Create different directions of moving 
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackAction = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackAction);

			enemy->runAction(spawn);
		}
		_moveCooldown -= dt;
	}
	if (enemy->getName().substr(0, 4) == "Wolf") {
		if (_moveCooldown <= 0) {
			_moveCooldown = MOVE_COOLDOWN;
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = MoveBy::create(1.5f, dest);

			enemy->runAction(moveAction);
		}
		_moveCooldown -= dt;
	}
 	if (enemy->getName().substr(0, 4) == "Boss") {
		if (_moveCooldown <= 0) {
			_moveCooldown = MOVE_COOLDOWN;
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			auto moveAction = MoveBy::create(1.5f, dest);
			Animation* attackAnimation = Animation::createWithSpriteFrames(enemy->getAttackFrames(), 0.13f);
			Animate* attackAnim = Animate::create(attackAnimation);
			auto attackAction = Repeat::create(attackAnim, 3);
			Action* spawn = Spawn::createWithTwoActions(moveAction, attackAction);

			enemy->runAction(spawn);
		}
		_moveCooldown -= dt;
	}
}

std::string AgressiveBehaviour::getBehaviourName() const {
	return "Agressive";
}
