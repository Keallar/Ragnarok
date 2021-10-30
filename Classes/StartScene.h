#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "box2d/b2dRootWorldNode.h"

enum class ePhysicsCategory {
    Player = 1,
    Platform = 2,
    All = 3
};

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float dt) override;
    void createSomePlayer(float dt);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void StartScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void tileMapInit();
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
private:
    CCTMXTiledMap* _tiledMap;
    CCTMXLayer* _background;
    CCTMXLayer* _walls;
    Player* _player;
    b2WorldNode* World;
};

