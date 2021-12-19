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
	IEnemyBehaviour* getBehaviour() const noexcept;
	void setHp(int hp) noexcept;
	void changeHp(float difHp);
	int getHp() const noexcept;
	void setSpeed(float speed) noexcept;
	float getSpeed() const noexcept;
	int getDamage() const noexcept;
	void setDamage(int damage) noexcept;
	void setAttackCooldown(float attackCooldown) noexcept;
	float getAttackCooldown() const noexcept;
	void setBulletSpeed(int bulletSpeed);
	void setDestroyed(bool state) noexcept;
	bool isDestroyed() const noexcept;
	void setDamaged(bool state) noexcept;
	bool isDamaged() const noexcept;
	void setAgressive(bool agressive) noexcept;
	bool isAgressive() const noexcept;
	void checkAgressive();
	void createHpLabel();
	void updateHpLabel();
	const cocos2d::Vector<SpriteFrame*> getIdleFrames() const;
	const cocos2d::Vector<SpriteFrame*> getAttackFrames() const;
	const cocos2d::Vector<SpriteFrame*> getMoveRightFrames() const;
	const cocos2d::Vector<SpriteFrame*> getMoveLeftFrames() const;

	virtual void update(float dt);
	virtual void shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator);
	virtual void setShootTarget(Vec2 target);
protected:
	IEnemyBehaviour* _behaviour;
	std::string _fileName;
	std::string _animationIdleFile;
	std::string _animationMoveLFile;
	std::string _animationMoveRFile;
	std::string _animationAttackFile;
	cocos2d::Vector<SpriteFrame*> _idleAnimFrames;
	cocos2d::Vector<SpriteFrame*> _attackAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveRightAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveLeftAnimFrames;
	int _bulletSpeed;
private:
	Vec2 _shootTarget;
	int _hp;
	float _speed;
	int _damage;
	bool _destroyed;
	bool _damaged;
	Label* _hpLabel;
	eAnimState _animState;
	bool _agressive;
};
