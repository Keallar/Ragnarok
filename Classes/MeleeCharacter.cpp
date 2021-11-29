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

void MeleeCharacter::meleeInit() {
	_hitTime = 0.2f;
	_damage = 100;
}