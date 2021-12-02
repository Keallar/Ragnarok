#include "BulletFactory.h"
#include "BigBullet.h"

#define CLEAR_TIMER 0

BulletFactory* BulletFactory::instance = nullptr;
int BulletFactory::id = -1;

BulletFactory* BulletFactory::getInstance() {
	if (instance != nullptr) {
		return instance;
	}

	instance = new BulletFactory;
	instance->_timer = CLEAR_TIMER;
	return instance;
}

void BulletFactory::setWorld(cocos2d::Node* world) {
	_world = dynamic_cast<b2WorldNode*>(world);
}

void BulletFactory::createBullet(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest) {
	
	auto bullet = bulletCreator->create(_world, pos, dest);
	_bullets.push_back(bullet);
}

Bullet* BulletFactory::getLastBullet() {
	return _bullets.back();
}

void BulletFactory::update(float dt) {

	for (auto bullet : _bullets) {
		if (bullet) {
			if (!(bullet->isRemoving())) {
				bullet->update(dt);
			}
		}
	}
	_timer -= dt;
	if (_timer <= 0) {
		clean();
		_timer = CLEAR_TIMER;
	}
}

void BulletFactory::clean() {

	for (auto bullet : _bullets) {
		if (bullet) {
			if (bullet->isRemoving()) {
				_world->removeChild(bullet);
				bullet = nullptr;
			}
		}
	}

	if (_bullets.size() != 0) {
		_bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(),
			[](Bullet* bullet) { return (!bullet || bullet->isRemoving()); }),
		_bullets.end());
	}
}