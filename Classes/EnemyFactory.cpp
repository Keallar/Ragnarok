#pragma once
#include "EnemyFactory.h"

EnemyFactory* EnemyFactory::instance = nullptr;

EnemyFactory* EnemyFactory::getInstance() {
    if (instance) {
        return instance;
    }
    instance = new EnemyFactory();
    return instance;
}

SimpleEnemy* EnemyFactory::createSimpleEnemy() {
    auto simpleEnemyObj = SimpleEnemy::createSimpleEnemy();
    return simpleEnemyObj;
}
