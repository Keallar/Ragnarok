#pragma once
#include "AgressiveBehaviour.h"
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

	}
	if (enemy->getName().substr(0, 6) == "Flying") {
		if (_moveCooldown <= 0) {
			_moveCooldown = MOVE_COOLDOWN;
			Vec2 pos = enemy->getPosition();
			Vec2 dest = targetPos - pos;
			Action* moveAction = MoveBy::create(1.5f, dest);
			//TODO Create different directions of moving 
			/*Animation* moveRightAnimation = Animation::createWithSpriteFrames(enemy->getMoveRightFrames(), 0.13f);
			Animate* moveRightAnim = Animate::create(moveRightAnimation);
			Action* moveRightAct = Repeat::create(moveRightAnim, 1);*/
			enemy->runAction(moveAction);
		}
		_moveCooldown -= dt;
	}
	if (enemy->getName().substr(0, 5) == "Aboba") {

	}
	if (enemy->getName().substr(0, 4) == "Wolf") {

	}
}

std::string AgressiveBehaviour::getBehaviourName() const {
	return "Agressive";
}
