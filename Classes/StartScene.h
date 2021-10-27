#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "box2d/b2dRootWorldNode.h"

enum class PhysicsCategory {
    player = 1,
    platform = 2,
    all = 3
};

class StartScene : public cocos2d::Scene
{
public:

    Player* _player;

    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float dt) override;

    void createSomePlayer(float dt);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void StartScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    b2WorldNode* World;
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

