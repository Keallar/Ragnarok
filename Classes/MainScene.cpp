#include <iostream>
#include <string>
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ContactListener.h"
#include "CCIMGUI.h"
#include "imgui.h"
#include "IdleBehaviour.h"
#include "Enemy.h"

#include "imgui/CCIMGUIGLViewImpl.h"
#include "imgui/CCImGuiLayer.h"
#include "imgui/CCIMGUI.h"
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

void MainScene::setFuncStr(std::string _funcStr) {
    funcStr = _funcStr;
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }  

    GameVars::initVars();

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _background = Sprite::create("images/Sky1.png");
    _background1 = Sprite::create("images/Sky2.png");
    _background1->setScaleX(1.2);
    _background2 = Sprite::create("images/Mounts1.png");
    _background2->setScaleX(1.35);
    _background3 = Sprite::create("images/Mounts2.png");
    _background3->setScaleX(1.5);
    addChild(_background);
    addChild(_background1);
    addChild(_background2);
    addChild(_background3);
    _background->setPosition({ 9000, 24000 });
    _background1->setPosition({ 9000, 24000 });
    _background2->setPosition({ 9000, 24000 });
    _background3->setPosition({ 9000, 24000 });
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
    _firstTileMap->getTiledMap()->getLayer("FG3")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG3.1")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG4")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG5")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG6")->setVisible(false);
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
    _player->setPosition({ 4000, 24000 });
    //_player->getBody()->SetBullet(true);

    save();
    _deathCount = 0;

    //bullet json loading
    Bullet::loadJson();

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
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mousePressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/background.mp3", true);

    CCIMGUI::getInstance()->addImGUI([=]() {
        showImGui(); }, "Function ID");

    Director::getInstance()->getScheduler()->schedule([=](float dt)
        {
            auto runningScene = Director::getInstance()->getRunningScene();
            if (runningScene && !runningScene->getChildByName("ImGUILayer"))
            {
                runningScene->addChild(ImGuiLayer::create(), INT_MAX, "ImGUILayer");
            }
        }, this, 0, false, "checkIMGUI");

    scheduleUpdate();

    return true;
}

void MainScene::restart() {
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _firstTileMap->getTiledMap()->getLayer("FG1")->setVisible(true);
    _firstTileMap->getTiledMap()->getLayer("FG1.2")->setVisible(true);
    _firstTileMap->getTiledMap()->getLayer("FG1.3")->setVisible(true);
    _firstTileMap->getTiledMap()->getLayer("FG2")->setVisible(true);
    _firstTileMap->getTiledMap()->getLayer("FG3")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG3.1")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG4")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG5")->setVisible(false);
    _firstTileMap->getTiledMap()->getLayer("FG6")->setVisible(false);
    
    _player->restart();

    _player->setPosition({ 4000, 24000 });

    save();
    _deathCount = 0;

    removeChild(_background4);
    _background->setTexture("images/Sky1.png");
    _background1->setTexture("images/Sky2.png");
    _background1->setScaleX(1.2);
    _background2->setTexture("images/Mounts1.png");
    _background2->setScaleX(1.35);
    _background3->setTexture("images/Mounts2.png");
    _background3->setScaleX(1.5);
    _background4 = nullptr;

    const auto playerHp = _player->getHp();
    const auto playerMana = _player->getMana();
    _hud->beginLife(playerHp, playerMana);

    BulletFactory::cleanAll();

    for (auto t : _triggers) {
        t->setIsActive(false);
    }

    for (auto enemy : enemies) {
        enemy->setDestroyed(true);
    }
}

void MainScene::update(float dt) {
    _world->update(dt);
    _world->removeIsDeletingChildren();

    BulletFactory::getInstance()->update(dt);

    if (_player) {
        if (_player->isDied()) {
            //_player->removeFromParent();
            //WTF ПЕРЕДЕЛАТЬ ИБО FPS КАТИТЬСЯ ВНИЗ
            //_hud->gameOver(_player);
            //_hud->gameOver(_player);
            if (_deathCount < 3) {
                load();
                _deathCount++;
            }
            else {
                _hud->gameOver(_player);
            }
            return;
        }
        _player->update(dt);
        const auto playerHp = _player->getHp();
        _hud->setHp(playerHp);
        const auto cameraPos = _player->getPosition();
        _background->setPosition(cameraPos);
        _background1->setPositionX(cameraPos.x+(9000-cameraPos.x)/115);
        _background1->setPositionY(cameraPos.y);
        _background2->setPositionX(cameraPos.x+(9000-cameraPos.x)/65);
        _background2->setPositionY(cameraPos.y);
        _background3->setPositionX(cameraPos.x + (9000 - cameraPos.x) / 45);
        _background3->setPositionY(cameraPos.y);
        if (_background4) {
            _background4->setPositionX(cameraPos.x + (9000 - cameraPos.x) / 30);
            _background4->setPositionY(cameraPos.y);
        }
        _cameraTarget->setPosition(cameraPos);


        if (funcStr != "") {
            funcStr.erase(0, 2);
            {
                int typeOfEnemy = (int)funcStr[0] - 48;
                static std::string type;
                switch (typeOfEnemy)
                {
                case 0:
                    type = "Simple";
                    break;
                case 1:
                    type = "Flying";
                    break;
                case 2:
                    type = "Wolf";
                    break;
                }
                funcStr.erase(0, 1);
                int xpos = std::stoi(funcStr.substr(0, 5));
                int ypos = std::stoi(funcStr.substr(5, 10));
                Vec2 pos = Vec2(_player->getPosition().x - xpos, _player->getPosition().y + ypos);
                createEnemyByTrigger(type, pos);
                funcStr = "";
            }
        }

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

void MainScene::save() {
    _save.playerSave = _player->save();
}

void MainScene::load() {
    _player->load(_save.playerSave);
}

void MainScene::createSomeEnemy(int count, std::string type) {
    if (_player) {
        for (auto i = 0; i < count; ++i) {
            const Vec2 pos = { _player->getPosition().x + 300, _player->getPosition().y + 100 };
			auto enemy = Enemy::create(_world, pos, type);
			enemies.push_back(enemy);
        }
    }
}

void MainScene::createBoss() {
    if (_player) {
        const Vec2 pos = { _player->getPosition().x + 300, _player->getPosition().y + 100 };
        auto boss = Boss::create(_world, pos, new BossIdleBehaviour);
        enemies.push_back(boss);
    }
}

void MainScene::createEnemyByTrigger(std::string type, Vec2 pos) {
    auto enemy = Enemy::create(_world, pos, type);
    enemies.push_back(enemy);
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
        if (ImGui::Button("Deathless")) {
            if (_player) {
                if (!_player->isDeathless()) {
                    _player->setDeathless(true);
                }
                else {
                    _player->setDeathless(false);
                }
            }
        }
        if (ImGui::Button("Save")) {
            if (!_player->isDied()) {
                save();
            }
        }
        if (ImGui::Button("Load")) {
            load();
        }
        if (ImGui::Button("FireBullet")) {
            if (_player) {
                _player->changeBulletCreator(new FireBulletCreator(ShootingCharacter::playerPhysMask(), _player));
            }
        }
        if (ImGui::Button("IdleBullet")) {
            if (_player) {
                _player->changeBulletCreator(new IdleBulletCreator(ShootingCharacter::playerPhysMask(), _player));
            }
        }
        if (ImGui::Button("IceBullet")) {
            if (_player) {
                _player->changeBulletCreator(new IceBulletCreator(ShootingCharacter::playerPhysMask(), _player));
            }
        }
        //Position
        ImGui::Text("Position X: %f Y: %f", _player->getPosition().x, _player->getPosition().y);
        //HP
        ImGui::Text("Hp: %i", _player->getHp());
        std::string deathless = "No";
        if (_player->isDeathless()) {
            deathless = "Yes";
        }
        else {
            deathless = "No";
        }
        ImGui::Text("Deathless: %s", deathless.c_str());
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
        static std::string eType = "Flying";
        ImGui::InputInt("Count of create enemies", &countOfEnemy, 0, 10);
        if (ImGui::Combo("Enemy Type", &enemyType, "Flying\0Simple\0Aboba\0Wolf")) {
            switch (enemyType)
            {
            case 0: eType = "Flying"; break;
            case 1: eType = "Simple"; break;
            case 2: eType = "Aboba"; break;
            case 3: eType = "Wolf"; break;
            }
        }
        if (ImGui::Button("CreateEnemy")) {
            createSomeEnemy(countOfEnemy, eType);
        }
        if (ImGui::Button("CreateBoss")) {
            createBoss();
        }
        if (ImGui::Button("DeleteLastEnemy")) {
            if (!enemies.empty()) {
                enemies.back()->setDestroyed(true);
            }
        }
        /*if (ImGui::Button("DeleteBoss")) {
            if (!enemies.empty()) {
                enemies.back()->setDestroyed(true);
            }
        }*/
        for (const auto& enemy : enemies) {
             ImGui::Text("%s position X: %f Y: %f", enemy->getName().c_str(), enemy->getPosition().x, enemy->getPosition().y);
        }
        ImGui::TreePop();
    }
    if(ImGui::Button("NoticeBox")) {
        _hud->messageOpen("hello world!\n hello world!\n hello world!");
    }
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

void MainScene::addTrigger(Trigger* trigger) {
    _triggers.push_back(trigger);
}

void MainScene::setCaveBG() {
    _background->setTexture("images/cave0.png");
    _background1->setTexture("images/cave1.png");
    _background2->setTexture("images/cave2.png");
    _background3->setTexture("images/cave3.png");
    _background4 = Sprite::create("images/cave4.png");
    _background4->setScaleX(1.6);
    addChild(_background4);
    _background->setZOrder(_player->getZOrder() - 5);
    _background1->setZOrder(_player->getZOrder() - 4);
    _background2->setZOrder(_player->getZOrder() - 3);
    _background3->setZOrder(_player->getZOrder() - 2);
    _background4->setZOrder(_player->getZOrder() - 1);
}