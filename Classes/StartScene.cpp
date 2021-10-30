#include "StartScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    return StartScene::create();
}

bool StartScene::init() {
    if (!Scene::init()) {
        return false;
    }    

    GameVars::initVars();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    DrawNode* background = DrawNode::create();
    background->drawSolidRect(origin, Director::getInstance()->getVisibleSize() + Size(origin), Color4F(1, 1, 1, 1));
    addChild(background);

    World = b2WorldNode::create(0, -98, 20);
    addChild(World);
    
    //auto floor = b2Sprite::create("pinky.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 0.0, 0.0);
    //auto wallL = b2Sprite::create("pinky.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 0.0, 0.0);
    //auto wallR = b2Sprite::create("pinky.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 0.0, 0.0);
    //auto ceil = b2Sprite::create("pinky.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 0.0, 0.0);
    tileMapInit();
    //World->addChild(floor);
    //World->addChild(wallL);
    //World->addChild(wallR);
    //World->addChild(ceil);

    //floor->setPosition((visibleSize.width) / 2 + origin.x, 2 + origin.y);
    //wallL->setPosition(2 + origin.x, (visibleSize.height + origin.y) / 2);
    //wallR->setPosition(visibleSize.width + origin.x - 2, (visibleSize.height + origin.y) / 2);
    //ceil->setPosition((visibleSize.width) / 2 + origin.x, visibleSize.height + origin.y - 2);

    _player = Player::createPlayer();
    //_player->setScale(0.5);

    Vec2 playerOrigin(Director::getInstance()->getWinSize()/2);

    World->addChild(_player);

    _player->getBody()->SetFixedRotation(true);

    _player->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate();    
    schedule(schedule_selector(StartScene::createSomePlayer), 0.5f);

    return true;
}

void StartScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_D:
        _player->setRunState(eRunState::Right);
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _player->setRunState(eRunState::Left);
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        if (_player->getJumpState() == eJumpState::None) {
            _player->setJumpState(eJumpState::Jump);
        }
        break;
    }
}

void StartScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_D:
        _player->setRunState(eRunState::Left);
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _player->setRunState(eRunState::Right);
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        _player->setJumpState(eJumpState::Fall);
        break;
    }
        
}

void StartScene::update(float dt) {
    _player->move();
    _player->jump();
    World->update(dt);
}

void StartScene::createSomePlayer(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Player* somePlayer = Player::createPlayer();
    World->addChild(somePlayer);
    Vec2 playerOrigin(Director::getInstance()->getWinSize() / 2);
    somePlayer->getBody()->SetFixedRotation(true);
    somePlayer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
}

void StartScene::tileMapInit() {
    _tiledMap = new CCTMXTiledMap();
     _tiledMap->initWithTMXFile("last.tmx");
    _background = _tiledMap->layerNamed("TileLayer1");
    _walls = _tiledMap->layerNamed("TileLayer2");
    Sprite* tile = new Sprite;
    for (float i = 0; i < _walls->getLayerSize().width; i++) {
        for (float j = 0; j < _walls->getLayerSize().height; j++) 
        {
            if (_walls->getTileAt({ i, j })) {
                auto _b2test = b2Sprite::create();
                _b2test->initWithSprite(_walls->getTileAt({ i, j }));
                _b2test->initBody(b2BodyType::b2_staticBody);
                World->addChild(_b2test);
                _b2test->setPosition(i * _walls->getTileAt({ i, j })->getTextureRect().size.width, (_tiledMap->getMapSize().height-j )* _walls->getTileAt({ i, j })->getTextureRect().size.height);
            }
        }
    }
}

