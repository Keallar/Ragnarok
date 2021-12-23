#include "MeleeCharacter.h"

MeleeCharacter::MeleeCharacter() {
	_isMeleeAttack = false;
	_meleeHit = nullptr;
	_time = 0;
}

void MeleeCharacter::update(float dt) {
	_time += dt;

	if (_hitTime - _time <= 0) {
		_isMeleeAttack = false;
		cleanHit();
		_meleeHit = nullptr;
		_time = 0;
	}
}

int MeleeCharacter::getMeleeDamage() const {
	return _damage;
}

void MeleeCharacter::meleeInit() {
	_hitTime = 0.2f;
	_damage = 100;
}

int MeleeHit::getDamage() {
	return _damage;
}

MeleeHit* MeleeHit::create(int damage) {
	MeleeHit* meleeHit = new (std::nothrow) MeleeHit();
	meleeHit->init();
	if (meleeHit && meleeHit->initWithFile("images/melee.png")) {
		meleeHit->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		meleeHit->autorelease();
		//bullet->init();
		meleeHit->_damage = damage;
		return meleeHit;
	}
	CC_SAFE_DELETE(meleeHit);
	return nullptr;
}