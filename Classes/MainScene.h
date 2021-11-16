#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "IEnemy.h"
#include "box2d/b2dRootWorldNode.h"
#include "bullet.h"
#include "UI.h"

enum class ePhysicsCategory {
    Player = 1,
    Platform = 2,
    All = 3
};

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    void update(float dt) override;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void mousePressed(cocos2d::Event* event);
    void createSomeEnemy(float dt);

    void tileMapInit();

    CREATE_FUNC(MainScene);
private:
    Player* _player;
    b2WorldNode* _world;
    cocos2d::Camera* _cameraTarget;
    UI* _ui;

    std::vector<IEnemy*> enemies;
};

