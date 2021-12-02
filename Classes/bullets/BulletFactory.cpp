#include "BulletFactory.h"
#include "BigBullet.h"
BulletFactory* BulletFactory::instance = nullptr;
int BulletFactory::id = -1;

BulletFactory* BulletFactory::getInstance() {
	if (instance != nullptr) {
		return instance;
	}

	instance = new BulletFactory;
	instance->_timer = 0;
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
		_timer = 0;
	}
}

void BulletFactory::clean() {

	for (std::vector<Bullet*>::iterator it = _bullets.begin(); it != _bullets.end(); it++) {
		auto bullet = *it;
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