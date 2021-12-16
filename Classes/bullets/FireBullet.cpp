#include "FireBullet.h"
#include <cmath>
#include "IShootingPattern.h"

bool FireBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_shootingPattern = new IdleShootingPattern(this);
	_attackCooldown = 0;
	
	initVars("FireBullet");

	_isOnRemove = false;
	_startedMove = false;
	_fireCount = 0;
	return true;
}

void FireBullet::update(float dt) {
	if (_fireCount < 2) {
		auto newDest = getDest();
		b2Filter filter;
		filter.categoryBits = getFixture()->GetFilterData().categoryBits;
		filter.maskBits = getFixture()->GetFilterData().maskBits;
		shoot(newDest, new FireBlastCreator(filter));
	}
	shootingCharacterUpdate(dt);
	Bullet::update(dt);
}

FireBullet* FireBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	FireBullet* bullet = new (std::nothrow) FireBullet();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		bullet->setCooldown();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void FireBullet::setCooldown() {
	Vec2 nDest = getDest();
	nDest.normalize();
	nDest *= 10;
	double k = getDest().x / nDest.x;
	_attackConstCooldown = 0.25*(1/k);//k;
}

void FireBullet::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {
		_attackCooldown = _attackConstCooldown;
		Vec2 pos = getPosition();
		Vec2 dest = targetPos; //+ pos;
		Vec2 newDest = dest;
		//newDest.rotate(Vec2(), 0.1f);
		newDest.normalize();
		newDest *= getContentSize().height;
		Vec2 pos1 = pos + newDest;
		//dest.y *= -1;
		//dest.normalize();
		//dest *= PLAYER_BULLET_SPEED;
		_shootingPattern->shoot(pos1, dest, bulletCreator);
		_fireCount++;
	}
}

int FireBullet::getDamage() {
	return 0;
}

bool FireBlast::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	
	initVars("FireBlast");

	_startedMove = false;
	_isOnRemove = false;
	_moveDest = Vec2();
	return true;
}

void FireBlast::update(float dt) {
	Bullet::update(dt);
}

FireBlast* FireBlast::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	FireBlast* bullet = new (std::nothrow) FireBlast();
	bullet->init();
	if (bullet && bullet->initWithFile(bullet->_fileName)) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		//bullet->init();
		bullet->setCoords(pos, dest);
		bullet->_moveDest = bullet->getDest();
		bullet->_moveDest.rotate(Vec2(), M_PI/2);
		bullet->setAngleMoveParam();
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void FireBlast::setAngleMoveParam() {
	Vec2 nDest = getDest();
	nDest.normalize();
	nDest *= 10;
	double k = getDest().x / nDest.x;
	_moveDest *= (0.66f);
	_moveAngle = M_PI * 2 / (30*(1/k));
}

int FireBlast::getDamage() {
	return 0;
}

void FireBlast::move(float dt) {

	_moveDest.rotate(Vec2(), _moveAngle);
	setPosition(getPosition() + _moveDest);
	//Vec2 sdest = getDest() + _moveDest;
	//dest *= dt / 0.016;
	//getBody()->SetLinearVelocity(b2Vec2(_moveDest.x, _moveDest.y));
	getBody()->SetLinearVelocity(b2Vec2(getDest().x, getDest().y));
	//getBody()->SetLinearVelocity(b2Vec2(getDest().x + _moveDest.x, getDest().y + _moveDest.y));
}