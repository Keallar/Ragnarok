#include "IBulletMoveBehavior.h"

IBulletMoveBehavior::IBulletMoveBehavior(Bullet* parent) : _parent(parent) {
	_startedMove = false;
	_timer = 0;
}

void BulletIdleBehavior::move(float dt) {
	if (!_startedMove) {
		_parent->getBody()->SetLinearVelocity(b2Vec2(_parent->getDest().x, _parent->getDest().y));
	}
}