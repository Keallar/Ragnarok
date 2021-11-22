#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class IBulletMoveBehavior;

class Bullet : public b2Sprite
{
public:
	Bullet();
	~Bullet();

	static Bullet* createBullet(Vec2 pos, Vec2 dest);
	static Bullet* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);

	virtual bool init();

	virtual void update(float dt);
	void ordinaryUpdate(float dt);

	float getMoveTime();
	float getLifeTime();

	virtual void collideFunc();

	void setOnRemove();
	bool isRemoving();

	Vec2 getDest();
	void setNewBehavior(IBulletMoveBehavior* behavior);

	virtual int getDamage();

protected:
	static float BULLET_MOVE_TIME;
	static float BIG_BULLET_MOVE_TIME;
	static float HOOK_BULLET_MOVE_TIME;
	static float HOOK_BULLET_LIFE_TIME;

	static int BULLET_DAMAGE;
	static int BIG_BULLET_DAMAGE;

	void setCoords(Vec2 pos, Vec2 dest);

	IBulletMoveBehavior* _moveBehavior;
	Vec2 _pos;
	Vec2 _dest;
	float _moveTime;
	float _lifeTime;
	bool _isOnRemove;
};