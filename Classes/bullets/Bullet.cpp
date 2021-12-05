#include "Bullet.h"

float Bullet::BULLET_MOVE_TIME = 2.0f;
float Bullet::BIG_BULLET_MOVE_TIME = 2.0f;
float Bullet::HOOK_BULLET_MOVE_TIME = 2;
float Bullet::HOOK_BULLET_LIFE_TIME = 7.0f;
float Bullet::ICE_BULLET_MOVE_TIME = 0.5f;
float Bullet::FIRE_BULLET_MOVE_TIME = 2.0f;


int Bullet::BULLET_DAMAGE = 100;
int Bullet::BIG_BULLET_DAMAGE = 150;


Bullet::Bullet() {
	b2Sprite::init();
}

Bullet::~Bullet() {

}

Bullet* Bullet::create(cocos2d::Node* world, Vec2 pos, Vec2 dest, b2Filter filter) {
	Bullet* bullet = new (std::nothrow) Bullet();
	if (bullet && bullet->initWithFile("bullet.png")) {
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


bool Bullet::init() {
	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });

	_moveTime = BULLET_MOVE_TIME;
	_lifeTime = BULLET_MOVE_TIME;
	_isOnRemove = false;
	_startedMove = false;
	return true;
}

void Bullet::update(float dt) {
	_moveTime -= dt;
	_lifeTime -= dt;
	move(dt);
	if (_moveTime <= 0 && getBody()->GetLinearVelocity() != b2Vec2(0, 0)) {
		getBody()->SetLinearVelocity(b2Vec2( 0, 0 ));
	}
	if (_lifeTime <= 0 && _isOnRemove != true) {
		setOnRemove();
	}
}

void Bullet::ordinaryOptions(cocos2d::Node* world, Vec2 pos) {
	world->addChild(this);
	this->setPosition(pos);
	this->getBody()->SetGravityScale(0);
}

void Bullet::setCoords(Vec2 pos, Vec2 dest) {
	_pos = pos;
	_dest = dest;
}

float Bullet::getMoveTime() {
	return _moveTime;
}

float Bullet::getLifeTime() {
	return _lifeTime;
}

void Bullet::setOnRemove() {
	_isOnRemove = true;
	b2Filter filter;
	filter.categoryBits = 0;
	filter.maskBits = 0;
	getBody()->GetFixtureList()->SetFilterData(filter);
}

bool Bullet::isRemoving() {
 	return _isOnRemove;
}

void Bullet::collideFunc() {
	setOnRemove();
}

int Bullet::getDamage() {
	return BULLET_DAMAGE;
}

void Bullet::move(float dt) {
	if (!_startedMove) {
		getBody()->SetLinearVelocity(b2Vec2(getDest().x, getDest().y));
		//_parent->setPosition(Vec2(_parent->getDest().x, _parent->getDest().y));
	}
	_startedMove = true;
}

Vec2 Bullet::getDest() {
	return _dest;
}

void Bullet::draw(Renderer* renderer, const Mat4& transform, uint32_t flags) {
	if (!_isOnRemove) {
		b2Sprite::draw(renderer, transform, flags);
	}
}