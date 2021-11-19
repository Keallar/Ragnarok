#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "IEnemy.h"
#include "box2d/b2dRootWorldNode.h"
#include "bullet.h"
#include "UI.h"

class MainScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    void update(float dt) override;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void mousePressed(cocos2d::Event* event);
    void createSomeEnemy(float dt);
    void showImGui();

    void tileMapInit();

    CREATE_FUNC(MainScene);
private:
    Player* _player;
    b2WorldNode* _world;
    cocos2d::Camera* _cameraTarget;
    cocos2d::Sprite* _background;
    UI* _ui;
    cocos2d::DrawNode* _test;

    std::vector<IEnemy*> enemies;
};

