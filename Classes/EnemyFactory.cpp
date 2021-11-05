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

SimpleEnemy* EnemyFactory::createSimpleEnemy(b2WorldNode* world, Vec2 pos) {
    id++;
    auto simpleEnemyObj = SimpleEnemy::createSimpleEnemy();
    //simpleEnemyObj->init();
    simpleEnemyObj->setName("simpleEnemy_" + std::to_string(id));
    b2Filter filter;
    filter.categoryBits = static_cast<uint16>(eColCategory::enemy);
    filter.maskBits = static_cast<uint16>(eColMask::enemy);
    simpleEnemyObj->getFixtureDef()->filter = filter;
    //auto hp = std::to_string(simpleEnemyObj->getHp());
    //auto hpLabel = Label::createWithTTF(hp, "fonts/Marker Felt.ttf", 24);
    world->addChild(simpleEnemyObj);
    simpleEnemyObj->getBody()->SetFixedRotation(true);
    simpleEnemyObj->setPosition(pos);
    //UNDONE
    simpleEnemyObj->createHpLabel();
    return simpleEnemyObj;
}
