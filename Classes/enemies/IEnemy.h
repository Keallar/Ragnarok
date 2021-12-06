#pragma once
#include "ShootingCharacter.h"

class IEnemyBehaviour;

class IEnemy : public ShootingCharacter, public b2Sprite {
	enum class eAnimState {
		None,
		Move,
		Attack
	};
public:
	IEnemy(IEnemyBehaviour* behaviour = nullptr);
	virtual ~IEnemy();
	void setBehaviour(IEnemyBehaviour* behaviour);
	void setHp(int hp) noexcept;
	void changeHp(float difHp);
	int getHp() const noexcept;
	void setSpeed(float speed) noexcept;
	float getSpeed() const noexcept;
	int getDamage() const noexcept;
	void setDamage(int damage) noexcept;
	void setAttackCooldown(float attackCooldown);
	float getAttackCooldown() const noexcept;
	void setDestroyed(bool state) noexcept;
	bool isDestroyed() const noexcept;
	void setDamaged(bool state) noexcept;
	bool isDamaged() const noexcept;
	void createHpLabel();
	void updateHpLabel();
	const cocos2d::Vector<SpriteFrame*> getIdleFrames() const;
	const cocos2d::Vector<SpriteFrame*> getAttackFrames() const;
	const cocos2d::Vector<SpriteFrame*> getMoveRightFrames() const;
	const cocos2d::Vector<SpriteFrame*> getMoveLeftFrames() const;

	virtual void update(float dt);
	virtual void shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator);
	virtual void setShootTarget(Vec2 target);

	static int BULLET_SPEED;
protected:
	IEnemyBehaviour* _behaviour;
	std::string _fileName;
	std::string _animationFile;
	cocos2d::Vector<SpriteFrame*> _idleAnimFrames;
	cocos2d::Vector<SpriteFrame*> _attackAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveRightAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveLeftAnimFrames;
private:
	Vec2 _shootTarget;
	int _hp;
	float _speed;
	int _damage;
	bool _destroyed;
	bool _damaged;
	float _attackCooldown;
	Label* _hpLabel;
	eAnimState _animState;
};
