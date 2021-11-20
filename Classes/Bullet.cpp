#include "Bullet.h"
#include "IBulletMoveBehavior.h"

float Bullet::BULLET_MOVE_TIME = 2.0f;
float Bullet::BIG_BULLET_MOVE_TIME = 2.0f;
float Bullet::HOOK_BULLET_MOVE_TIME = 0.5f;

int Bullet::BULLET_DAMAGE = 100;
int Bullet::BIG_BULLET_DAMAGE = 150;

Bullet::Bullet() {
	b2Sprite::init();
}

Bullet::~Bullet() {

}

Bullet* Bullet::createBullet(Vec2 pos, Vec2 dest) {
	auto bullet = Bullet::create("bullet.png", b2BodyType::b2_dynamicBody, 0.f, 0);
	bullet->init();
	bullet->setCoords(pos, dest);
	bullet->setNewBehavior(new BulletIdleBehavior(bullet));
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
	_moveBehavior->move(dt);
	if (_moveTime <= 0) {
		getBody()->SetLinearVelocity(b2Vec2{ 0, 0 });
	}
	if (_lifeTime <= 0) {
		setOnRemove();
	}
}

bool Bullet::init() {
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

float Bullet::getLifeTime() {
	return _lifeTime;
}

void Bullet::setOnRemove() {
	_isOnRemove = true;
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

void Bullet::setNewBehavior(IBulletMoveBehavior* behavior) {
	_moveBehavior = behavior;
}

Vec2 Bullet::getDest() {
	return _dest;
}