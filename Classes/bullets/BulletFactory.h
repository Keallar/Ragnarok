#pragma once
#include "Bullet.h"
#include "box2d/b2dRootWorldNode.h"
#include "IBulletTypeCreator.h"
#include <list>

class BulletFactory {
public:
	static BulletFactory* getInstance();
	static void cleanAll();

	void update(float dt);

	void setWorld(cocos2d::Node* world);

	//temp
	Bullet* getLastBullet();

	void createBullet(IBulletTypeCreator* bulletCreator, Vec2 pos, Vec2 dest);
private:
	static BulletFactory* instance;

	void clean();

	float _timer;
	
	std::list<std::list<Bullet*>::iterator> removeList;

	b2WorldNode* _world;
	std::list<Bullet*> _bullets;
	std::list<Bullet*> _removeList;
	static int id;
};

