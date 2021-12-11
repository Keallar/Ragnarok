#include <iostream>
#include <string>
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ContactListener.h"
#include "CCIMGUI.h"
#include "imgui.h"
#include "IdleBehaviour.h"
#include "Enemy.h"
#include "NoticeBox.h"

USING_NS_CC;

Player* MainScene::getPlayer() {
    return _player;
}

TileMapManager* MainScene::getTMM() {
    return _firstTileMap;
}

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

    //DrawNode* background = DrawNode::create();
    //background->drawSolidRect(origin-backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(1, 1, 1, 1));
    //addChild(background);

    //DrawNode* background = DrawNode::create();
    //const Vec2 backSize{ 5000, 5000 };
    //background->drawSolidRect(origin-backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(0, 0, 0, 1));
    //addChild(background);

    //World init
    _world = b2WorldNode::create(0, -98, 20);
    addChild(_world);
    BulletFactory::getInstance()->setWorld(_world);

    //World->debugDraw();

    //ContactListener init
    _world->getb2World()->SetContactListener(new ContactListener);

    // TILEMAP INITION СЮДА НЕ СМОТРЕТЬ
    // И НИЧЕГО НЕ ТРОГАТЬ, МОЁ
    //TileMap init
    _firstTileMap = TileMapManager::createTileMap();
    addChild(_firstTileMap->getTiledMap());
    _firstTileMap->setTiledMap("maximum.tmx");
    _firstTileMap->addLayer("Collidable", "Collidable");
    _firstTileMap->addLayer("ObjectLayer", "ObjectLayer");
    _firstTileMap->CollidableLayerInit(_world, _firstTileMap->getLayerByName("Collidable"));
    _firstTileMap->TileMapObjectLayerInit(_world);

    //_firstTileMap->TileMapBackgroundLayerInit(smth, _firstTileMap->getLayerByName("FG"));

    //Creating player
    _player = Player::create();
    const Vec2 playerOrigin { Director::getInstance()->getWinSize() / 2 };
    _world->addChild(_player);
    _player->getBody()->SetFixedRotation(true);
    _player->setPosition({ 8000, 22000 });
    //_player->getBody()->SetBullet(true);

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

    CCIMGUI::getInstance()->addImGUI([=]() {
        showImGui(); }, "Function ID");

    scheduleUpdate();

    /*_test = DrawNode::create();
    _test->setName("DrawNode");
    addChild(_test);*/

    /*NoticeBox* nBox = NoticeBox::create();
    auto tempLabel = Label::create();
    tempLabel->setString("Hello World!");
    nBox->printText(tempLabel);
    addChild(nBox);*/

    return true;
}

void MainScene::update(float dt) {
    _world->update(dt);
    _world->removeIsDeletingChildren();

    BulletFactory::getInstance()->update(dt);

    if (_player) {
        if (_player->isDied()) {
            _player->removeFromParent();
            //WTF ПЕРЕДЕЛАТЬ ИБО FPS КАТИТЬСЯ ВНИЗ
            _hud->gameOver(_player);

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
            const auto targetPos = _player->getPosition();
            enemy->setShootTarget(targetPos);
        }
        enemy->update(dt);
        if (enemy) {
            if (enemy->isDestroyed()) {
                enemy->setOnRemove();
            }
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](IEnemy* enemy) { return enemy->isDestroyed(); }),
        enemies.end());

    _hud->setPosition(_cameraTarget->getPosition() - Director::getInstance()->getVisibleSize()/2);

    //_rayCastManager->castAllRaysOfTileMapManager(_firstTileMap->getCallbacks(), _firstTileMap->getRays(),
    //    _world, _player, _firstTileMap->getTiledMap());

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

void MainScene::createSomeEnemy(int count, std::string type) {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    if (_player) {
        for (auto i = 0; i < count; ++i) {
            const Vec2 pos = { _player->getPosition().x + 100, _player->getPosition().y + 100 };
            if (type == "Simple") {
                auto enemy = Enemy::create(_world, pos, type, new IdleBehaviour);
                enemies.push_back(enemy);
            } 
            else if (type == "Flying") {
                auto enemy = Enemy::create(_world, pos, type, new IdleBehaviour);
                enemies.push_back(enemy);
            }
        }
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
        //Position
        ImGui::Text("Position X: %f Y: %f", _player->getPosition().x, _player->getPosition().y);
        //HP
        ImGui::Text("Hp: %i", _player->getHp());
        //Double jump
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
        //Player Anim state
        std::string animStateInfo = "None";
        if (_player->getAnimState() == eAnimState::None)
            animStateInfo = "None";
        else if (_player->getAnimState() == eAnimState::Move)
            animStateInfo = "Move";
        else if (_player->getAnimState() == eAnimState::Jump)
            animStateInfo = "Jump";
        else if (_player->getAnimState() == eAnimState::Fall)
            animStateInfo = "Fall";
        else if (_player->getAnimState() == eAnimState::Attack)
            animStateInfo = "Attack";
        ImGui::Text("AnimState: %s", animStateInfo.c_str());

        ImGui::TreePop();
    }
    //Enemies info
    if (ImGui::TreeNode("Enemies")) {
        static int countOfEnemy = 1;
        static int enemyType = -1;
        static std::string eType;
        ImGui::InputInt("Count of create enemies", &countOfEnemy, 0, 10);
        if (ImGui::Combo("Enemy Type", &enemyType, "Flying")) {
            switch (enemyType)
            {
            case 0: eType = "Simple"; break;
            case 1: eType = "Flying"; break;
            case 2: eType = "Aboba"; break;
            case 3: eType = "Wolf"; break;
            }
        }
        if (ImGui::Button("CreateEnemy")) {
            createSomeEnemy(countOfEnemy, eType);
        }
        if (ImGui::Button("DeleteLastEnemy")) {
            if (!enemies.empty()) {
                enemies.back()->setDestroyed(true);
            }
        }
        for (const auto& enemy : enemies) {
             ImGui::Text("%s position X: %f Y: %f", enemy->getName().c_str(), enemy->getPosition().x, enemy->getPosition().y);
        }
        ImGui::TreePop();
    }
    /*if(ImGui::Button("NoticeBox")) {
        NoticeBox* nBox = NoticeBox::create();
        auto tempLabel = Label::create();
        tempLabel->setString("Hello World!");
        nBox->printText(tempLabel);
        addChild(nBox);
    }*/
    static bool isTouchedDrawNode = false;
    if (ImGui::Button("DebugNode")) {
        if (!isTouchedDrawNode) {
            isTouchedDrawNode = true;
        }
        else {
            isTouchedDrawNode = false;
        }
        if (isTouchedDrawNode) {
            ccDrawLine(_player->getPosition(), { 0, 0 });
        }
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
    static bool isToucedStyleEditor = false;
    if (ImGui::Button("StyleEditor")) {
        if (!isToucedStyleEditor) {
            isToucedStyleEditor = true;
        }
        else {
            isToucedStyleEditor = false;
        }
    }
    if (isToucedStyleEditor) {
        ImGui::ShowStyleEditor();
    }
    ImGui::End();
}
