#include "FireBullet.h"
#include <cmath>
#include "IShootingPattern.h"

bool FireBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_shootingPattern = new IdleShootingPattern(this);
	_attackCooldown = 0;
	_moveTime = FIRE_BULLET_MOVE_TIME;
	_lifeTime = FIRE_BULLET_MOVE_TIME;
	_isOnRemove = false;
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
	if (bullet && bullet->initWithFile("images/BigFire.png")) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		bullet->init();
		bullet->setCoords(pos, dest);
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void FireBullet::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {
		_attackCooldown = 0.5;
		Vec2 pos = getPosition();
		Vec2 dest = targetPos; //+ pos;
		Vec2 newDest = dest;
		newDest.rotate(Vec2(), 0.9f);
		newDest.normalize();
		newDest *= getContentSize().height;
		Vec2 pos1 = pos + newDest;
		//dest.y *= -1;
		dest.normalize();
		dest *= PLAYER_BULLET_SPEED;
		_shootingPattern->shoot(pos1, dest, bulletCreator);
		_fireCount++;
	}
}

int FireBullet::getDamage() {
	return 0;
}

bool FireBlast::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = FIRE_BULLET_MOVE_TIME;
	_lifeTime = FIRE_BULLET_MOVE_TIME;
	_isOnRemove = false;
	_moveDest = Vec2();
	return true;
}

void FireBlast::update(float dt) {
	Bullet::update(dt);
}

FireBlast* FireBlast::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	FireBlast* bullet = new (std::nothrow) FireBlast();
	if (bullet && bullet->initWithFile("images/Fire.png")) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		bullet->init();
		bullet->setCoords(pos, dest);
		bullet->_moveDest = bullet->getDest();
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

int FireBlast::getDamage() {
	return 0;
}

void FireBlast::move(float dt) {

	_moveDest.rotate(Vec2(), 360/60 );
	getBody()->SetLinearVelocity(b2Vec2(getDest().x + _moveDest.x, getDest().y + _moveDest.y));
}