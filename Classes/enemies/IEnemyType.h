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
	cocos2d::Vector<SpriteFrame*> getIdleFrames() { return _idleAnimFrames; }
	cocos2d::Vector<SpriteFrame*> getAttackFrames() { return _attackAnimFrames; }
	cocos2d::Vector<SpriteFrame*> getMoveRightFrames() { return _moveRightAnimFrames; }
	cocos2d::Vector<SpriteFrame*> getMoveLeftFrames() { return _moveLeftAnimFrames; }
protected:
	std::string _fileName;
	std::string _enemyName;
	b2Filter _filter;
	int _hp;
	int _damage;
	float _speed;
	float _attackCooldown;
	int _bulletSpeed;
	cocos2d::Vector<SpriteFrame*> _idleAnimFrames;
	cocos2d::Vector<SpriteFrame*> _attackAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveRightAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveLeftAnimFrames;
};
