#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <string>

USING_NS_CC;

class IEnemyType {
public:
	virtual ~IEnemyType() {};
	virtual std::string getTypeName() const = 0;
	std::string getFileName() const { return _fileName; }
	std::string getName() const { return _enemyName; }
	b2Filter getFilter() const noexcept { return _filter; }
	int getHp() const noexcept { return _hp; }
	int getDamage() const noexcept { return _damage; }
	float getSpeed() const noexcept { return _speed; }
	float getAttackCooldown() const noexcept { return _attackCooldown; }
	Animate* getIdleAnimate() const noexcept { if (_idleAnim) return _idleAnim;  }
protected:
	std::string _fileName;
	std::string _enemyName;
	b2Filter _filter;
	int _hp;
	int _damage;
	float _speed;
	float _attackCooldown;
	int _bulletSpeed;
	Animate* _idleAnim;
};
