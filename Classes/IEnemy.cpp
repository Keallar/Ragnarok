#include "IEnemy.h"

USING_NS_CC;

void IEnemy::setHp(float& hp) {
	if (!hp) {
		return;
	}
	_hp = hp;
}

float IEnemy::getHp() const {
	return _hp;
}

void IEnemy::setDestroyed(bool& state) {
	_destroyed = state;
}

bool IEnemy::isDestroyed() const {
	return _destroyed;
}

void IEnemy::setDamaged(bool& state) {
	_damaged = state;
}

bool IEnemy::isDamaged() const {
	return _damaged;
}