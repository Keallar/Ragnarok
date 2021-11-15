#pragma once
#include "EnemyFactory.h"

EnemyFactory* EnemyFactory::instance = nullptr;
int EnemyFactory::id = -1;

EnemyFactory* EnemyFactory::getInstance() {
    if (instance) {
        return instance;
    }
    instance = new EnemyFactory();
    return instance;
}

Enemy* EnemyFactory::createSimpleEnemy(b2WorldNode* world, Vec2 pos) {
    id++;
    auto enemyObj = Enemy::create("hero.png", b2BodyType::b2_dynamicBody, 0.f, 0);
    enemyObj->setName("simpleEnemy_" + std::to_string(id));
    b2Filter filter;
    filter.categoryBits = static_cast<uint16>(eColCategory::enemy);
    filter.maskBits = static_cast<uint16>(eColMask::enemy);
    enemyObj->getFixtureDef()->filter = filter;
    world->addChild(enemyObj);
    enemyObj->getBody()->SetFixedRotation(true);
    enemyObj->setPosition(pos);
    //UNDONE
    enemyObj->createHpLabel();
    return enemyObj;
}
