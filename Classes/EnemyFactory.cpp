#pragma once
#include "EnemyFactory.h"
#include "IEnemyType.h"
#include "IEnemyBehaviour.h"
#include "SimpleEnemy.h"

EnemyFactory* EnemyFactory::instance = nullptr;
int EnemyFactory::id = -1;

EnemyFactory* EnemyFactory::getInstance() {
    if (instance) {
        return instance;
    }
    instance = new EnemyFactory();
    return instance;
}

Enemy* EnemyFactory::createEnemy(b2WorldNode* world, Vec2 pos, IEnemyType* type, IEnemyBehaviour* behaviour) {
    id++;
    auto enemyObj = Enemy::create(b2BodyType::b2_dynamicBody, 0.f, 0, type, behaviour);
    enemyObj->setName(enemyObj->getName() + std::to_string(id));
    world->addChild(enemyObj);
    enemyObj->getBody()->SetFixedRotation(true);
    enemyObj->setPosition(pos);
    //UNDONE
    enemyObj->createHpLabel();
    return enemyObj;
}
