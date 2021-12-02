#include "IceBullet.h"
#include "IBulletMoveBehavior.h"
#include "IShootingPattern.h"
#include <cmath>

bool IceBullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_shootingPattern = new TripleShootingPattern(this);
	_attackCooldown = 0;
	_moveTime = ICE_BULLET_MOVE_TIME;
	_lifeTime = ICE_BULLET_MOVE_TIME;
	_stoped = false;
	_isOnRemove = false;
	return true;
}

void IceBullet::update(float dt) {
	_moveTime -= dt;
	_lifeTime -= dt;
	_moveBehavior->move(dt);
	if (_moveTime <= 0) {
		Bullet::getBody()->SetLinearVelocity(b2Vec2{ 0, 0 });
	}
	if (_lifeTime <= 0) {
		_stoped = true;
	}
	if (_stoped) {
		auto dest = Vec2(Bullet::getBody()->GetLinearVelocity().x, Bullet::getBody()->GetLinearVelocity().y);

		shoot(dest, new PlayerIceBlastCreator);
		Bullet::setOnRemove();
	}
}

void IceBullet::collideFunc() {
	_stoped = true;
}

IceBullet* IceBullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	IceBullet* bullet = new (std::nothrow) IceBullet();
	if (bullet && bullet->Bullet::initWithFile("Ice.png")) {
		bullet->Bullet::initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->Bullet::autorelease();
		bullet->init();
		bullet->setCoords(pos, dest);
		bullet->setNewBehavior(new BulletIdleBehavior(bullet));
		bullet->Bullet::getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

int IceBullet::getDamage() {
	return 0;
}

bool IceBullet::isStoped() {
	return _stoped;
}

void IceBullet::shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator) {
	if (_attackCooldown <= 0) {

		Vec2 pos = Bullet::getPosition();
		Vec2 dest = targetPos - pos;
		dest.normalize();
		dest *= PLAYER_BULLET_SPEED;

		_shootingPattern->shoot(pos, dest, bulletCreator);
	}
}

bool IceBlast::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = BIG_BULLET_MOVE_TIME;
	_lifeTime = BIG_BULLET_MOVE_TIME;
	_isOnRemove = false;
	return true;
}

void IceBlast::update(float dt) {
	ordinaryUpdate(dt);
}

IceBlast* IceBlast::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	IceBlast* bullet = new (std::nothrow) IceBlast();
	if (bullet && bullet->initWithFile("IceBlast.png")) {
		bullet->initBody(b2BodyType::b2_dynamicBody, 0.f, 0);
		bullet->autorelease();
		bullet->init();
		bullet->setCoords(pos, dest);
		bullet->setNewBehavior(new BulletIdleBehavior(bullet));
		bullet->getFixtureDef()->filter = filter;
		bullet->ordinaryOptions(world, pos);
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

int IceBlast::getDamage() {
	return 0;
}
