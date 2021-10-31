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
    background->drawSolidRect(origin, Director::getInstance()->getVisibleSize() + Size(origin), Color4F(1, 1, 1, 1));
    addChild(background);

    _world = b2WorldNode::create(0, -98, 20);
    addChild(_world);

    //_world->getb2World()->SetContactListener(new ContactListener);

    //World->debugDraw();
    
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

    /*floor->setName("platform");
    wallL->setName("platform");
    wallR->setName("platform");
    ceil->setName("platform");*/
    _player = Player::createPlayer();
    //_player->setScale(0.5);

    Vec2 playerOrigin { Director::getInstance()->getWinSize() / 2 };

    _world->addChild(_player);

    _player->getBody()->SetFixedRotation(true);
    _player->setName("player");

    _player->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate();
    //schedule(schedule_selector(MainScene::removeSomePlayer), 2.5f);
    schedule(schedule_selector(MainScene::removeSomeEnemy), 0.5f);

    return true;
}

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    _player->keyPressed(keyCode, event);
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    _player->KeyReleased(keyCode, event);
}

void MainScene::update(float dt) {
    _player->move();
    _player->jump();
    _world->update(dt);
    _world->removeIsDeletingChildren();
}

//UNDONE
//������! �������� ����������
static int id = 0;
void MainScene::removeSomeEnemy(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    SimpleEnemy* enemy = SimpleEnemy::createSimpleEnemy();
    _world->addChild(enemy);
    enemy->setName("simpleEnemy_" + std::to_string(id));
    Vec2 playerOrigin(Director::getInstance()->getWinSize() / 2);
    enemy->getBody()->SetFixedRotation(true);
    enemy->setPosition(visibleSize.width / 2, visibleSize.height / 2);
}

void MainScene::tileMapInit() {
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
                _world->addChild(_b2test);
                _b2test->setPosition(i * _walls->getTileAt({ i, j })->getTextureRect().size.width, (_tiledMap->getMapSize().height-j )* _walls->getTileAt({ i, j })->getTextureRect().size.height);
            }
        }
    }
}

