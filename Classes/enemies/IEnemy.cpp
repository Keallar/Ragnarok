#pragma once
#include "IEnemy.h"
#include "IShootingPattern.h"
#include "IEnemyBehaviour.h"

int IEnemy::BULLET_SPEED = 10;

IEnemy::IEnemy(IEnemyType* type, IEnemyBehaviour* behaviour) {
	_shootingPattern = new IdleShootingPattern(this);
	_type = type;
	_behaviour = behaviour;
}

IEnemy::~IEnemy() {
	delete _hpLabel;
	delete _type;
	delete _behaviour;
}

void IEnemy::update(float dt) {
	_behaviour->perform(this);
	//if (_behaviour == )
	shoot(_shootTarget, new EnemyIdleBulletCreator);
	shootingCharacterUpdate(dt);
	updateHpLabel();
	_attackCooldown -= dt;
}

void IEnemy::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {
		_attackCooldown = ENEMY_ATTACK_COOLDOWN;
		Vec2 pos = getPosition();
		Vec2 dest = targetPos - pos;
		dest.normalize();
		//dest *= BULLET_SPEED;
		//dest *= 10;

		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

void IEnemy::setShootTarget(Vec2 target) {
	_shootTarget = target;
}

void IEnemy::setHp(int hp) noexcept {
	_hp = hp;
}

void IEnemy::changeHp(float difHp) {
	_hp += difHp;
	setDamaged(false);
	if (_hp <= 0) {
		setDestroyed(true);
	}
	if (!_hpLabel) {
		return;
	}
	_hpLabel->setString(std::to_string(_hp));
}

int IEnemy::getHp() const noexcept {
	return _hp;
}

void IEnemy::setSpeed(float speed) noexcept {
	_speed = speed;
}

float IEnemy::getSpeed() const noexcept {
	return _speed;
}

int IEnemy::getDamage() const noexcept {
	return _damage;
}

void IEnemy::setDamage(int damage) noexcept {
	_damage = damage;
}

void IEnemy::setDestroyed(bool state) noexcept {
	_destroyed = state;
}

bool IEnemy::isDestroyed() const noexcept {
	return _destroyed;
}

void IEnemy::setDamaged(bool state) noexcept {
	_damaged = state;
}

bool IEnemy::isDamaged() const noexcept{
	return _damaged;
}

void IEnemy::createHpLabel() {
	_hpLabel = Label::createWithTTF(std::to_string(_hp), "fonts/Marker Felt.ttf", 16);
	if (!_hpLabel) {
		CCLOG("Error in createHpLabel IEnemy");
		return;
	}
	_hpLabel->setTextColor(Color4B(0, 0, 0, 200));
	addChild(_hpLabel);
	const auto posX = getOffsetPosition().x;
	const auto posY = getOffsetPosition().y;
	const auto width = getTextureRect().size.width;
	const auto height = getTextureRect().size.height;
	_hpLabel->setPosition(posX + width/2, posY + height);
}

void IEnemy::updateHpLabel() {
	_hpLabel->setString(std::to_string(_hp));
}

void IEnemy::setBehaviour(IEnemyBehaviour* behaviour) {
	delete _behaviour;
	_behaviour = behaviour;
}

void IEnemy::setType(IEnemyType* type) {
	delete _type;
	_type = type;
}

IEnemyType* IEnemy::getType() const {
	if (!_type) {
		return nullptr;
	}
	return _type;
}