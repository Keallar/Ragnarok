#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "SimpleEnemy.h"
#include "box2d/b2dRootWorldNode.h"
#include <proj.win32/TileMapManager.h>
#include "RayCastManager.h"

enum class ePhysicsCategory {
    Player = 1,
    Platform = 2,
    All = 3
};

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt) override;
    void createSomePlayer(float dt);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void removeSomeEnemy(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
private:
    Player* _player;
    b2WorldNode* _world;
    cocos2d::Camera* _cameraTarget;
    TileMapManager* _firstTileMap = TileMapManager::createTileMap();
    RayCastManager* _rayCastManager;

};

