#pragma once
#include "Bullet.h"
#include "box2d/b2dRootWorldNode.h"
#include "IBulletTypeCreator.h"

class BulletFactory
{
public:
	static BulletFactory* getInstance();

	void update(float dt);

	void setWorld(cocos2d::Node* world);

	//temp
	Bullet* getLastBullet();

	void createBullet(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest);
private:
	static BulletFactory* instance;

	void clean();

	float _timer;

	b2WorldNode* _world;
	std::vector<Bullet*> _bullets;
	std::list<Bullet*> _removeList;
	static int id;
};

