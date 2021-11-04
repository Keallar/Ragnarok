#include "IEnemy.h"

USING_NS_CC;

void IEnemy::setHp(float hp) noexcept {
	if (!hp) {
		return;
	}
	_hp = hp;
}

void IEnemy::changeHp(float difHp) noexcept {
	if (_hp <= 0) {
		return;
	}
	_hp -= difHp;
}

float IEnemy::getHp() const {
	return _hp;
}

void IEnemy::setDestroyed(bool& state) noexcept {
	_destroyed = state;
}

bool IEnemy::isDestroyed() const {
	return _destroyed;
}

void IEnemy::setDamaged(bool& state) noexcept {
	_damaged = state;
}

bool IEnemy::isDamaged() const {
	return _damaged;
}