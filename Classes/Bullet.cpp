#include "Bullet.h"

float Bullet::BULLET_MOVE_TIME = 2.0f;

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
	_moveTime -= dt;
}

bool Bullet::init() {
	if (!b2Sprite::init()) {
		return false;
	}

	setCoords(Vec2{ 0, 0 }, Vec2{ 0, 0 });
	_moveTime = BULLET_MOVE_TIME;
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