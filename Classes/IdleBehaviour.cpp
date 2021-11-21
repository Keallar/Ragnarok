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
		if (state == static_cast<int>(eIdleState::MoveLeft)) {
			enemy->setPositionX(enemy->getPosition().x - 2);
		}
		if (state == static_cast<int>(eIdleState::MoveRight)) {
			enemy->setPositionX(enemy->getPosition().x + 2);
		}
	}
}

std::string IdleBehaviour::getBehaviourName() const {
	return "IdleBehaviour";
}
