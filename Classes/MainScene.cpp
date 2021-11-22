#include <iostream>
#include <string>
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ContactListener.h"
#include "EnemyFactory.h"
#include <TileMapManager.h>
#include "imgui/CCIMGUI.h"
#include "imgui/imgui.h"
#include "SimpleEnemy.h"
#include "IdleBehaviour.h"

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

    DrawNode* background = DrawNode::create();
    //background->drawSolidRect(origin-backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(1, 1, 1, 1));
    //addChild(background);

    //DrawNode* background = DrawNode::create();
    const Vec2 backSize{ 5000, 5000 };
    //background->drawSolidRect(origin-backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(1, 1, 1, 1));
    //addChild(background);

    //World init
    _world = b2WorldNode::create(0, -98, 20);
    addChild(_world);

    //World->debugDraw();

    // TILEMAP INITION СЮДА НЕ СМОТРЕТЬ
    // И НИЧЕГО НЕ ТРОГАТЬ, МОЁ
    //ContactListener init
    auto contactListener = new ContactListener;
    _world->getb2World()->SetContactListener(contactListener);

    //TileMap init
    TileMapManager* _firstTileMap = TileMapManager::createTileMap();
    addChild(_firstTileMap->getTiledMap());
    _firstTileMap->setTiledMap("maximum.tmx");
    _firstTileMap->addLayer("Collidable", "Collidable");
    _firstTileMap->CollidableLayerInit(_world, _firstTileMap->getLayerByName("Collidable"));
    //_firstTileMap->TileMapBackgroundLayerInit(smth, _firstTileMap->getLayerByName("FG"));

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
    _hud = HUD::create();
    const auto playerHp = _player->getHp();
    const auto playerMana = _player->getMana();
    _hud->beginLife(playerHp, playerMana);
    addChild(_hud);

    //HandleEvents init
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mousePressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate();

    CCIMGUI::getInstance()->addImGUI([=]() {
        showImGui(); }, "Function ID");

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
        _hud->setHp(playerHp);
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

    _hud->setPosition(_cameraTarget->getPosition() - Director::getInstance()->getVisibleSize()/2);
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

void MainScene::createSomeEnemy(float dt) {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    if (_player) {
        const Vec2 pos = { _player->getPosition().x + 100, _player->getPosition().y + 100 };
        auto enemy = EnemyFactory::getInstance()->createEnemy(_world, pos, new SimpleEnemy, new IdleBehaviour);
        enemies.push_back(enemy);
    }
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
        ImGui::Text("Position X: %f Y: %f", _player->getPosition().x, _player->getPosition().y);
        ImGui::Text("Double Jump: %i",_player->getJumpCount());
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
    //Enemies info
    if (ImGui::TreeNode("Enemies")) {
        if (ImGui::Button("CreateEnemy")) {
            createSomeEnemy(0);
        }
        if (ImGui::Button("DeleteLastEnemy")) {
            if (!enemies.empty()) {
                enemies[enemies.size() - 1]->setDestroyed(true);
            }
        }
        for (const auto& enemy : enemies) {
             ImGui::Text("%s position X: %f Y: %f", enemy->getName().c_str(), enemy->getPosition().x, enemy->getPosition().y);
        }
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
    ImGui::End();
}
