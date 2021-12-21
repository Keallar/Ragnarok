#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "IEnemy.h"
#include "b2dRootWorldNode.h"
#include "bullet.h"
#include "HUD.h"
#include "RayCastManager.h"
#include "TileMapManager.h"
#include "Trigger.h"

struct Save {
    PlayerSave playerSave;
};

class MainScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    void update(float dt) override;
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void mousePressed(cocos2d::Event* event);

    void createEnemyByTrigger(std::string type, Vec2 pos);
    void createSomeEnemy(int count, std::string type);
    void showImGui();

    void tileMapInit();

    void save();
    void load();
    void restart();

    Player* getPlayer();
    TileMapManager* getTMM();

    void setFuncStr(std::string _funcStr);
    void addTrigger(Trigger* trigger);

    CREATE_FUNC(MainScene);
private:
    Player* _player;
    Save _save;

    int _deathCount;

    std::string funcStr;

    b2WorldNode* _world;
    cocos2d::Camera* _cameraTarget;
    cocos2d::Sprite* _background;
    cocos2d::Sprite* _background1;
    cocos2d::Sprite* _background2;
    cocos2d::Sprite* _background3;
    HUD* _hud;
    cocos2d::DrawNode* _test;
    RayCastManager* _rayCastManager;
    TileMapManager* _firstTileMap;

    std::list<IEnemy*> enemies;
    std::list<Trigger*> _triggers;
};
