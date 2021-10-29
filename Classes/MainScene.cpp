#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ContactListener.h"

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

    _world->getb2World()->SetContactListener(new ContactListener);

    //World->debugDraw();
    
    auto floor = b2Sprite::create("pinky.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 0.0, 0.0);
    auto wallL = b2Sprite::create("pinky.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 0.0, 0.0);
    auto wallR = b2Sprite::create("pinky.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 0.0, 0.0);
    auto ceil = b2Sprite::create("pinky.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 0.0, 0.0);

    _world->addChild(floor);
    _world->addChild(wallL);
    _world->addChild(wallR);
    _world->addChild(ceil);

    floor->setPosition((visibleSize.width) / 2 + origin.x, 2 + origin.y);
    wallL->setPosition(2 + origin.x, (visibleSize.height + origin.y) / 2);
    wallR->setPosition(visibleSize.width + origin.x - 2, (visibleSize.height + origin.y) / 2);
    ceil->setPosition((visibleSize.width) / 2 + origin.x, visibleSize.height + origin.y - 2);

    floor->setName("platform");
    wallL->setName("platform");
    wallR->setName("platform");
    ceil->setName("platform");

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

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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
    enemy->setName("somePlayer" + std::to_string(id));
    Vec2 playerOrigin(Director::getInstance()->getWinSize() / 2);
    enemy->getBody()->SetFixedRotation(true);
    enemy->setPosition(visibleSize.width / 2, visibleSize.height / 2);
}