#pragma once
#include "ShootingCharacter.h"
#include "MeleeCharacter.h"

class IEnemyBehaviour;

class IEnemy : public ShootingCharacter, public MeleeCharacter, public b2Sprite {
	enum class eAnimState {
		None,
		Move,
		Attack
	};
public:
	IEnemy(IEnemyBehaviour* behaviour = nullptr);
	virtual ~IEnemy();
	void setBehaviour(IEnemyBehaviour* behaviour);
	void setIdleBehaviour();
	void setAgressiveBehaviour();
	IEnemyBehaviour* getBehaviour() const noexcept;
	void setHp(int hp) noexcept;
	void changeHp(float difHp);
	int getHp() const noexcept;
	void setSpeed(float speed) noexcept;
	float getSpeed() const noexcept;
	int getDamage() const noexcept;
	void setDamage(int damage) noexcept;
	void setBulletDamage(int damage) noexcept;
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
	void setShootingPattern(std::string shootingPatternInfo);

	//Label
	void createHpLabel();
	void updateHpLabel();

	virtual void update(float dt);
	virtual void shoot(Vec2 targetPos, IBulletTypeCreator* bulletCreator);
	virtual Vec2 getShootTarget() const;
	virtual void setShootTarget(Vec2 target);

	//Animation
	const cocos2d::Vector<SpriteFrame*> getIdleFrames() const;
	const cocos2d::Vector<SpriteFrame*> getAttackFrames() const;
	const cocos2d::Vector<SpriteFrame*> getMoveFrames() const;

	//Melee Func
	void hit() override;
	void cleanHit() override;
	void meleeInit() override;
	virtual void meleeUpdate(float dt);
protected:
	std::string _type;
	IEnemyBehaviour* _behaviour;
	std::string _fileName;
	std::string _animationIdleFile;
	std::string _animationMoveFile;
	std::string _animationAttackFile;
	cocos2d::Vector<SpriteFrame*> _idleAnimFrames;
	cocos2d::Vector<SpriteFrame*> _attackAnimFrames;
	cocos2d::Vector<SpriteFrame*> _moveAnimFrames;
	int _bulletSpeed;
	int _agressiveZone;

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
