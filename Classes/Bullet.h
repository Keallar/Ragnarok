#pragma once
#include "cocos2d.h"
#include "box2d/b2dSprite.h"

class Bullet : public b2Sprite
{
public:
	Bullet();
	~Bullet();

	static Bullet* createPlayerBullet(Vec2 pos, Vec2 dest);

	static Bullet* createBullet(Vec2 pos, Vec2 dest);
	static Bullet* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);

	virtual bool init();

	void update(float dt) override;

	float getMoveTime();

	void setOnRemove();
	bool isRemoving();

private:
	static float BULLET_MOVE_TIME;
	
	void setCoords(Vec2 pos, Vec2 dest);

	Vec2 _pos;
	Vec2 _dest;
	float _moveTime;
	bool _isOnRemove;
};

