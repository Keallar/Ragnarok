#include <iostream>
#include <string>
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ContactListener.h"
#include "EnemyFactory.h"
#include <proj.win32/TileMapManager.h>
#include "SimpleEnemy.h"
#include "imgui/CCIMGUI.h"
#include "imgui/imgui.h"

USING_NS_CC;

Scene* MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }    

    GameVars::initVars();

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //_background = Sprite::create("background.png");
    //_background->setContentSize(Director::getInstance()->getWinSize());
    //addChild(_background);

    //DrawNode* background = DrawNode::create();
    //const Vec2 backSize{ 5000, 5000 };
    //background->drawSolidRect(origin-backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(0, 0, 0, 1));
    //addChild(background);

    //World init
    _world = b2WorldNode::create(0, -98, 20);
    addChild(_world);

    //ContactListener init
    auto contactListener = new ContactListener;
    _world->getb2World()->SetContactListener(contactListener);

    //TileMap init
    TileMapManager* _firstTileMap = TileMapManager::createTileMap();
    _firstTileMap->setTiledMap("Test.tmx");
    _firstTileMap->addLayer("Foreground", "FG");
    _firstTileMap->CollidableLayerInit(_world, _firstTileMap->getLayerByName("Foreground"));

    //Creating player
    _player = Player::createPlayer();
    const Vec2 playerOrigin { Director::getInstance()->getWinSize() / 2 };
    b2Filter filter;
    filter.categoryBits = static_cast<uint16>(eColCategory::player);
    filter.maskBits = static_cast<uint16>(eColMask::player);
    _player->getFixtureDef()->filter = filter;
    _world->addChild(_player);
    _player->getBody()->SetFixedRotation(true);
    _player->setName("player");
    _player->setPosition(8000, 22000);
    _player->getBody()->SetBullet(true);

    //Camera setup
    _cameraTarget = getDefaultCamera();
    
    //_background->setPosition(_cameraTarget->getPosition());

    //Creating UI
    _ui = UI::create();
    const auto playerHp = _player->getHp();
    _ui->beginLife(playerHp);
    const auto playerMana = _player->getMana();
    _ui->beginMana(playerMana);
    addChild(_ui);

    //HandleEvents init
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mousePressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate();

    //createSomeEnemy(0);

    CCIMGUI::getInstance()->addImGUI([=](){
        showImGui(); } , "Function ID");


    return true;
}

void MainScene::update(float dt) {
    _world->update(dt);
    _world->removeIsDeletingChildren();

    if (_player) {
        if (_player->isDied()) {
            _player->cleanFunc();
            _player->removeFromParent();
            return;
        }
        _player->update(dt);
        const auto playerHp = _player->getHp();
        _ui->setHp(playerHp);
        const auto cameraPos = _player->getPosition();
        _cameraTarget->setPosition(cameraPos);
    }

    for (auto enemy : enemies) {
        if (_player) {
            const auto playerPos = _player->getPosition();
            enemy->setShootTarget(playerPos);
        }
        enemy->update(dt);
        if (enemy) {
            if (enemy->isDestroyed()) {
                enemy->cleanFunc();
                enemy->setOnRemove();
            }
        }
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](IEnemy* enemy) { return enemy->isDestroyed(); }),
        enemies.end());

    _ui->setPosition(_cameraTarget->getPosition() - Director::getInstance()->getVisibleSize()/2);
    //_background->setPosition(_cameraTarget->getPosition());
}

void MainScene::mousePressed(cocos2d::Event* event) {
    if (!_player) {
        return;
    }
    _player->mousePressed(event);
}

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_player) {
        return;
    }
    _player->keyPressed(keyCode, event);
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (!_player) {
        return;
    }
    _player->KeyReleased(keyCode, event);
}

void MainScene::showImGui() {
    if (!ImGui::Begin("Debug")) {
        ImGui::End();
        return;
    }
    if (ImGui::TreeNode("Player")) {
        if (ImGui::Button("UpHp")) {
            if (_player) {
                _player->changeHp(1);
            }
        }
        if (ImGui::Button("DownHp")) {
            if (_player) {
                _player->changeHp(-1);
            }
        }
        //Player jump
        std::string jumpInfo = "None";
        if (_player->getJumpState() == eJumpState::None)
            jumpInfo = "None";
        else if (_player->getJumpState() == eJumpState::Jump)
            jumpInfo = "Jump";
        else if (_player->getJumpState() == eJumpState::Fall)
            jumpInfo = "Fall";
        ImGui::Text("JumpInfo: %s", jumpInfo.c_str());

        ImGui::TreePop();
    }
    static bool isToucedMetric = false;
    if (ImGui::Button("Metrics")) {
        if (!isToucedMetric) {
            isToucedMetric = true;
        } 
        else {
            isToucedMetric = false;
        }
    }
    if (isToucedMetric) {
        ImGui::ShowMetricsWindow();
    }
    if (ImGui::Button("CreateEnemy")) {
        createSomeEnemy(0);
    }
    ImGui::End();
}

void MainScene::createSomeEnemy(float dt) {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    if (_player) {
        const Vec2 pos = { _player->getPosition().x + 100, _player->getPosition().y + 100 };
        auto enemy = EnemyFactory::getInstance()->createEnemy(_world, pos, new SimpleEnemy);
        enemies.push_back(enemy);
    }
}
