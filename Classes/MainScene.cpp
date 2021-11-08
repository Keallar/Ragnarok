#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ContactListener.h"
#include "EnemyFactory.h"

USING_NS_CC;

Scene* MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }    

    GameVars::initVars();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    DrawNode* background = DrawNode::create();
    Vec2 backSize{ 5000, 5000 };
    background->drawSolidRect(origin-backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(1, 1, 1, 1));
    addChild(background);

    _world = b2WorldNode::create(0, -98, 20);
    addChild(_world);

    auto contactListener = new ContactListener;
    _world->getb2World()->SetContactListener(contactListener);

    tileMapInit();
    
    //Creating player
    _player = Player::createPlayer();
    Vec2 playerOrigin { Director::getInstance()->getWinSize() / 2 };
    b2Filter filter;
    filter.categoryBits = static_cast<uint16>(eColCategory::player);
    filter.maskBits = static_cast<uint16>(eColMask::player);
    _player->getFixtureDef()->filter = filter;
    _world->addChild(_player);
    _player->getBody()->SetFixedRotation(true);
    _player->setName("player");
    _player->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    _player->getBody()->SetBullet(true);
    //camera setup
    _cameraTarget = getDefaultCamera();

    //Creating UI
    _ui = UI::create();
    const auto playerHp = _player->getHp();
    _ui->beginLife(playerHp);
    const auto playerMana = _player->getMana();
    _ui->beginMana(playerMana);
    addChild(_ui);

    //init HandleEvents
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mousePressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate();
    //schedule(schedule_selector(MainScene::createSomeEnemy), 0.5f);
    createSomeEnemy(0);
    return true;
}

void MainScene::update(float dt) {
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](IEnemy* enemy) { return enemy->isDestroyed(); }),
        enemies.end());

    _world->update(dt);
    _world->removeIsDeletingChildren();

    for (auto enemy : enemies) {
        enemy->setShootTarget(_player->getPosition());
        enemy->update(dt);
    }

    _player->update(dt);

    for (auto enemy : enemies) {
        if (enemy) {
            if (enemy->isDestroyed()) {
                enemy->setOnRemove();
            }
        }
    }

    auto playerHp = _player->getHp();
    _ui->setHp(playerHp);
    _cameraTarget->setPosition(_player->getPosition().x, Director::getInstance()->getVisibleSize().height / 2);
    //_ui->setPos(_player->getPosition().x, Director::getInstance()->getVisibleSize().height / 2);
}

void MainScene::mousePressed(cocos2d::Event* event) {
    _player->mousePressed(event);
}

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    _player->keyPressed(keyCode, event);
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    _player->KeyReleased(keyCode, event);
}

void MainScene::createSomeEnemy(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 pos = { visibleSize.width / 2, visibleSize.height / 2 };
    auto enemy = EnemyFactory::getInstance()->createSimpleEnemy(_world, pos);
    enemies.push_back(enemy);
}

void MainScene::tileMapInit() {
    _tiledMap = new CCTMXTiledMap();
    _tiledMap->initWithTMXFile("last.tmx");
    _background = _tiledMap->layerNamed("TileLayer1");
    _walls = _tiledMap->layerNamed("TileLayer2");
    Sprite* tile = new Sprite;
    for (float i = 0; i < _walls->getLayerSize().width; i++) {
        for (float j = 0; j < _walls->getLayerSize().height; j++) {
            if (_walls->getTileAt({ i, j })) {
                auto _b2test = b2Sprite::create();
                _b2test->initWithSprite(_walls->getTileAt({ i, j }));
                _b2test->initBody(b2BodyType::b2_staticBody);
                _b2test->setName("platform");
                b2Filter filter;
                filter.categoryBits = static_cast<uint16>(eColCategory::platform);
                filter.maskBits = static_cast<uint16>(eColMask::platform);
                _b2test->getFixtureDef()->filter = filter;
                _world->addChild(_b2test);
                _b2test->setPosition(i * _walls->getTileAt({ i, j })->getTextureRect().size.width, (_tiledMap->getMapSize().height-j )* _walls->getTileAt({ i, j })->getTextureRect().size.height);
            }
        }
    }
}

