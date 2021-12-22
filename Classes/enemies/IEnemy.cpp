#pragma once
#include "IEnemy.h"
#include "IShootingPattern.h"
#include "IEnemyBehaviour.h"
#include "AgressiveBehaviour.h"
#include "IdleBehaviour.h"

IEnemy::IEnemy(IEnemyBehaviour* behaviour) {
	_behaviour = behaviour;
}

IEnemy::~IEnemy() {
	delete _hpLabel;
	delete _behaviour;
	if (!_shootingPattern) {
		delete _shootingPattern;
	}
}

void IEnemy::meleeInit() {
	_hitTime = 0.3f;
	MeleeCharacter::_damage = 1;
}

void IEnemy::update(float dt) {
	if (isAgressive() && getBehaviour()->getBehaviourName().substr(0, 9) != "Agressive") {
		setAgressiveBehaviour();
	}
	else if (!isAgressive() && getBehaviour()->getBehaviourName().substr(0, 9) == "Agressive"){
		setIdleBehaviour();
	}
	_behaviour->perform(this, _shootTarget, dt);
	checkAgressive();
	shootingCharacterUpdate(dt);
	meleeUpdate(dt);
	updateHpLabel();
	_attackCooldown -= dt;
}

void IEnemy::meleeUpdate(float dt) {
	MeleeCharacter::update(dt);
	if (_meleeHit) {
		_meleeHit->setPosition(getPosition().x + 64, getPosition().y);
		if (getScaleX() < 0) {
			_meleeHit->setScaleX(getScaleX());
			_meleeHit->setPosition(getPosition().x - 64, getPosition().y);
		}
	}
}

void IEnemy::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {
		_attackCooldown = ENEMY_ATTACK_COOLDOWN;
		Vec2 pos = getPosition();
		Vec2 dest = targetPos - pos;
		dest.normalize();
		dest *= _bulletSpeed;

		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

void IEnemy::hit() {
	if (_meleeHit == nullptr) {
		_isMeleeAttack = true;
		MeleeCharacter::_time = 0;
		_meleeHit = b2Sprite::create("images/melee.png");
		b2Filter filter;
		filter.categoryBits = static_cast<int>(eColCategory::enemyMelee);
		filter.maskBits = static_cast<int>(eColMask::enemyMelee);
		_meleeHit->getFixtureDef()->filter = filter;
		getParent()->addChild(_meleeHit);
		_meleeHit->setPosition(getPosition().x - 64, getPosition().y);
		if (getScaleX() > 0) {
			_meleeHit->setScaleX(getScaleX());
			_meleeHit->setPosition(getPosition().x + 64, getPosition().y);
		}
	}
}

void IEnemy::cleanHit() {
	getParent()->removeChild(_meleeHit);
}

Vec2 IEnemy::getShootTarget() const {
	return _shootTarget;
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
	if (getPositionX() - _shootTarget.x < _agressiveZone && getPositionY() - _shootTarget.y < _agressiveZone &&
			getPositionX() - _shootTarget.x > -_agressiveZone && getPositionY() - _shootTarget.y > -_agressiveZone) {
		setAgressive(true);
	}
	else {
		setAgressive(false);
	}
}

void IEnemy::setShootingPattern(std::string shootingPatternInfo) {
	if (!_shootingPattern) {
		delete _shootingPattern;
	}

	if (shootingPatternInfo == "Idle") {
		_shootingPattern = new IdleShootingPattern(this);
	}
	else if (shootingPatternInfo == "ShotGun") {
		_shootingPattern = new ShotGunShootingPattern(this);
	}
	else if (shootingPatternInfo == "Circle") {
		_shootingPattern = new CircleShootingPattern(this);
	}
	else if (shootingPatternInfo == "Triple") {
		_shootingPattern = new TripleShootingPattern(this);
	}
	else if (shootingPatternInfo == "ParalRev") {
		//_shootingPattern = new ParalRevShootingPattern(this);
	}
	else {
		_shootingPattern = nullptr;
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
	if (getScaleX() < 0 && _hpLabel->getScaleX() > 0) {
		auto hpLabelScaleX = _hpLabel->getScaleX();
		_hpLabel->setScaleX(-hpLabelScaleX);
	}
	else if (getScaleX() > 0 && _hpLabel->getScaleX() < 0) {
		auto hpLabelScaleX = _hpLabel->getScaleX();
		_hpLabel->setScaleX(-hpLabelScaleX);
	}
}

const cocos2d::Vector<SpriteFrame*> IEnemy::getIdleFrames() const {
	return _idleAnimFrames;
}

const cocos2d::Vector<SpriteFrame*> IEnemy::getAttackFrames() const {
	return _attackAnimFrames;
}

const cocos2d::Vector<SpriteFrame*> IEnemy::getMoveFrames() const {
	return _moveAnimFrames;
}

void IEnemy::setIdleBehaviour() {
	if (_type == "Simple") {
		setBehaviour(new SimpleIdleBehaviour);
	}
	else if (_type == "Flying") {
		setBehaviour(new FlyingIdleBehaviour);
	}
	else if (_type == "Aboba") {
		setBehaviour(new AbobaIdleBehaviour);
	}
	else if (_type == "Wolf") {
		setBehaviour(new WolfIdleBehaviour);
	}
	else if (_type == "Boss") {
		setBehaviour(new BossIdleBehaviour);
	}
}

void IEnemy::setAgressiveBehaviour() {
	if (_type == "Simple") {
		setBehaviour(new SimpleAgressiveBehaviour);
	}
	else if (_type == "Flying") {
		setBehaviour(new FlyingAgressiveBehaviour);
	}
	else if (_type == "Aboba") {
		setBehaviour(new AbobaAgressiveBehaviour);
	}
	else if (_type == "Wolf") {
		setBehaviour(new WolfAgressiveBehaviour);
	}
	else if (_type == "Boss") {
		setBehaviour(new BossAgressiveBehaviour);
	}
}

void IEnemy::setBehaviour(IEnemyBehaviour* behaviour) {
	if (!_behaviour) {
		delete _behaviour;
	}
	_behaviour = behaviour;
}

IEnemyBehaviour* IEnemy::getBehaviour() const noexcept {
	return _behaviour;
}
