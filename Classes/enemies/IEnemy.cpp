#pragma once
#include "IEnemy.h"
#include "IShootingPattern.h"
#include "IEnemyBehaviour.h"
#include "AgressiveBehaviour.h"
#include "IdleBehaviour.h"

IEnemy::IEnemy(IEnemyBehaviour* behaviour) {
	_shootingPattern = new CircleShootingPattern(this);
	_behaviour = behaviour;
}

IEnemy::~IEnemy() {
	//WTF
	if (_hpLabel && _behaviour && _shootingPattern) {
		delete _hpLabel;
		delete _behaviour;
		delete _shootingPattern;
	}
}

void IEnemy::update(float dt) {
	if (isAgressive() && getBehaviour()->getBehaviourName() != "Agressive") {
		setBehaviour(new AgressiveBehaviour);
	}
	else if (!isAgressive() && getBehaviour()->getBehaviourName() == "Agressive"){
		setBehaviour(new IdleBehaviour);
	}
	_behaviour->perform(this, _shootTarget, dt);
	checkAgressive();
	shoot(_shootTarget, new IdleBulletCreator(enemyPhysMask()));
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
		dest *= _bulletSpeed;
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

void IEnemy::setAttackCooldown(float attackCooldown) noexcept {
	_attackCooldown = attackCooldown;
}

float IEnemy::getAttackCooldown() const noexcept {
	return _attackCooldown;
}

void IEnemy::setBulletSpeed(int bulletSpeed) {
	_bulletSpeed = bulletSpeed;
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

void IEnemy::setAgressive(bool agressive) noexcept {
	_agressive = agressive;
}

bool IEnemy::isAgressive() const noexcept {
	return _agressive;
}

void IEnemy::checkAgressive() {
	auto tempX = getPositionX() - _shootTarget.x;
	auto tempY = getPositionY() - _shootTarget.y;
	if (getPositionX() - _shootTarget.x < 400 && getPositionY() - _shootTarget.y < 400 &&
			getPositionX() - _shootTarget.x > -400 && getPositionY() - _shootTarget.y > -400) {
		setAgressive(true);
	}
	else {
		setAgressive(false);
	}
}
void IEnemy::createHpLabel() {
	_hpLabel = Label::createWithTTF(std::to_string(_hp), "fonts/Marker Felt.ttf", 16);
	if (!_hpLabel) {
		CCLOG("Error in createHpLabel IEnemy");
		return;
	}
	_hpLabel->setTextColor(Color4B(255, 255, 255, 200));
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

const cocos2d::Vector<SpriteFrame*> IEnemy::getIdleFrames() const {
	return _idleAnimFrames;
}

const cocos2d::Vector<SpriteFrame*> IEnemy::getAttackFrames() const {
	return _attackAnimFrames;
}

const cocos2d::Vector<SpriteFrame*> IEnemy::getMoveRightFrames() const {
	return _moveRightAnimFrames;
}

const cocos2d::Vector<SpriteFrame*> IEnemy::getMoveLeftFrames() const {
	return _moveLeftAnimFrames;
}

void IEnemy::setBehaviour(IEnemyBehaviour* behaviour) {
	delete _behaviour;
	_behaviour = behaviour;
}

IEnemyBehaviour* IEnemy::getBehaviour() const noexcept {
	return _behaviour;
}
