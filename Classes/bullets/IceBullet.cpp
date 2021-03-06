#include "IceBullet.h"
#include "IShootingPattern.h"
#include <cmath>

bool IceBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_shootingPattern = new TripleShootingPattern(this);
	_attackCooldown = 0;
	
	initVars("IceBullet");

	_startedMove = false;
	_stoped = false;
	_isOnRemove = false;
	return true;
}

void IceBullet::update(float dt) {
	_moveTime -= dt;
	_lifeTime -= dt;
	move(dt);
	if (_lifeTime <= 0) {
		_stoped = true;
	}
	if (_stoped) {
		auto dest = Vec2(getBody()->GetLinearVelocity().x, getBody()->GetLinearVelocity().y);

		b2Filter filter;
		filter.categoryBits = getFixture()->GetFilterData().categoryBits;
		filter.maskBits = getFixture()->GetFilterData().maskBits;
		shoot(dest, new IceBlastCreator(filter, this));
		setOnRemove();
	}
	if (_moveTime <= 0) {
		getBody()->SetLinearVelocity(b2Vec2{ 0, 0 });
	}
}

void IceBullet::collideFunc() {
	_stoped = true;
}

IceBullet* IceBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent) {
	IceBullet* bullet = new (std::nothrow) IceBullet();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->_parent = parent;
		bullet->_damage = parent->getDamage();
		bullet->_bulletDamage = bullet->_damage / 3;
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool IceBullet::isStoped() {
	return _stoped;
}

void IceBullet::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {

		Vec2 pos = getPosition();
		Vec2 dest = targetPos; //+ pos;
		//dest.y *= -1;
		dest.normalize();
		dest *= PLAYER_BULLET_SPEED;
		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

bool IceBlast::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	
	initVars("IceBlast");

	_startedMove = false;
	_isOnRemove = false;
	return true;
}

void IceBlast::update(float dt) {
	Bullet::update(dt);
}

IceBlast* IceBlast::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter, ShootingCharacter* parent) {
	IceBlast* bullet = new (std::nothrow) IceBlast();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->_parent = parent;
		bullet->_damage = parent->getDamage();
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

