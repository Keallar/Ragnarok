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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 45);
    edgeBody->setCategoryBitmask(static_cast<int>(PhysicsCategory::platform));
    //edgeBody->setContactTestBitmask(static_cast<int>(PhysicsCategory::all));
    edgeBody->setContactTestBitmask(static_cast<int>(PhysicsCategory::player));

    Node* edgeNode = Node::create();
    edgeNode->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    edgeNode->setPhysicsBody(edgeBody);
    addChild(edgeNode);

    DrawNode* background = DrawNode::create();
    background->drawSolidRect(origin, Director::getInstance()->getVisibleSize() + Size(origin), Color4F(1, 1, 1, 1));
    addChild(background);

    _player = Player::createPlayer();
    _player->setScale(0.5);

    Vec2 playerOrigin(Director::getInstance()->getWinSize()/2);
    _player->setPosition(playerOrigin);
    _player->getPhysicsBody()->setCategoryBitmask(static_cast<int>(PhysicsCategory::player));
    _player->getPhysicsBody()->setContactTestBitmask(static_cast<int>(PhysicsCategory::platform));
    _player->getPhysicsBody()->setContactTestBitmask(static_cast<int>(PhysicsCategory::platform));


    addChild(_player);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(StartScene::onKeyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate(); 
    schedule(schedule_selector(StartScene::createSomePlayer), 1.5f);

    /*createSomePlayer(0);*/

     

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactPreSolve = CC_CALLBACK_2(StartScene::onContactPreSolve, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void StartScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_D:
        _player->setRunState(runState::right);
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _player->setRunState(runState::left);
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        if (_player->getJumpState() == jumpState::none || true) {
            _player->setJumpState(jumpState::jump);
        }
        break;
    }
}

void StartScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_D:
        _player->setRunState(runState::left);
        break;
    case EventKeyboard::KeyCode::KEY_A:
        _player->setRunState(runState::right);
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        _player->setJumpState(jumpState::fall);
        break;
    }
        
}

void StartScene::update(float dt) {
    _player->move();
    _player->jump();
}

void StartScene::createSomePlayer(float dt) {
    Player* somePlayer = Player::createPlayer();
    Vec2 playerOrigin(Director::getInstance()->getWinSize() / 2);
    somePlayer->setPosition(playerOrigin);
    somePlayer->setScale(0.5f);
    somePlayer->getPhysicsBody()->setCategoryBitmask(static_cast<int>(PhysicsCategory::player));
    somePlayer->getPhysicsBody()->setContactTestBitmask(static_cast<int>(PhysicsCategory::platform));
    somePlayer->getPhysicsBody()->setDynamic(true);
    addChild(somePlayer);
}

/*bool StartScene::onContactPreSolve(PhysicsContact& contact,
    PhysicsContactPreSolve& solve) {


   /* auto nodeA = contact.getShapeA()->getBody();
    auto nodeB = contact.getShapeB()->getBody();

    Vec2 A = nodeA->getVelocity();
    A.normalize();

    Vec2 B = nodeB->getVelocity();
    B.normalize();
    
    

    if (nodeA->isDynamic()) {
        nodeA->setVelocity(Vec2(20*A.x,20*A.y));
    }
    if (nodeB->isDynamic()) {
        nodeB->setVelocity(Vec2(-20*B.x, -20*B.y));
    }*/

    //nodeA->setVelocity(-nodeA->getVelocity());
    //nodeB->setVelocity(-nodeB->getVelocity());

    /*return true;
}*/

bool StartScene::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
    /*auto nodeA = contact.getShapeA()->getBody();
    auto nodeB = contact.getShapeB()->getBody();

    nodeA->setVelocity(Vec2(0, 0));
    nodeB->setVelocity(Vec2(0, 0));*/

    solve.setSurfaceVelocity(Vec2(0, 0));

    return true;
}