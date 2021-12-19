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
	instance->_timer = 0.f;
	return instance;
}

void BulletFactory::cleanAll() {
	if (instance != nullptr) {
		for (auto bullet : instance->_bullets) {
			if (bullet) {
				instance->_world->removeChild(bullet);
				instance->_removeList.push_back(bullet);
			}
		}

		for (auto it : instance->_removeList) {
			instance->_bullets.erase(std::remove(instance->_bullets.begin(), instance->_bullets.end(), it));
		}
		instance->_removeList.clear();
	}
}

void BulletFactory::createBullet(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest) {
	
	auto bullet = bulletCreator->create(_world, pos, dest);
	_bullets.push_back(bullet);
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
		_timer = 0.f;
	}
}

void BulletFactory::clean() {

	for (auto bullet : _bullets) {
		if (bullet) {
			if (bullet->isRemoving()) {
				_world->removeChild(bullet);
				_removeList.push_back(bullet);
			}
		}
	}

	for (auto it : _removeList) {
		_bullets.erase(std::remove(_bullets.begin(), _bullets.end(), it));
	}
	_removeList.clear();
}

void BulletFactory::setWorld(cocos2d::Node* world) {
	_world = dynamic_cast<b2WorldNode*>(world);
}

Bullet* BulletFactory::getLastBullet() {
	return _bullets.back();
}