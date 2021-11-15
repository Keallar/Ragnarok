#include "Bullet.h"

float Bullet::BULLET_MOVE_TIME = 2.0f;
float Bullet::BIG_BULLET_MOVE_TIME = 2.0f;

int Bullet::BULLET_DAMAGE = 100;
int Bullet::BIG_BULLET_DAMAGE = 150;

Bullet::Bullet() {
	init();
}

Bullet::~Bullet() {

}

Bullet* Bullet::createBullet(Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::create("bullet.png", b2BodyType::b2_dynamicBody, 0.f, 0);
	bullet->setCoords(pos, dest);
	return bullet;
}

Bullet* Bullet::create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution) {
	Bullet* sprite = new (std::nothrow) Bullet();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->initBody(type, friction, restitution);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Bullet::update(float dt) {
	ordinaryUpdate(dt);
}

void Bullet::ordinaryUpdate(float dt) {
	_moveTime -= dt;
	_lifeTime -= dt;
	if (_moveTime <= 0) {
		getBody()->SetLinearVelocity(b2Vec2{ 0, 0 });
	}
	if (_lifeTime <= 0) {
		setOnRemove();
	}
}

bool Bullet::init() {
	if (!b2Sprite::init()) {
		return false;
	}

	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = BULLET_MOVE_TIME;
	_lifeTime = BULLET_MOVE_TIME;
	_isOnRemove = false;
	return true;
}

void Bullet::setCoords(Vec2 pos, Vec2 dest) {
	_pos = pos;
	_dest = dest;
}

float Bullet::getMoveTime() {
	return _moveTime;
}

void Bullet::setOnRemove() {
	_isOnRemove = true;
}

bool Bullet::isRemoving() {
	return _isOnRemove;
}

int Bullet::getDamage() {
	return BULLET_DAMAGE;
}