#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "EnemyContactListener.h"
#include "PlayerContactListener.h"
#include "EnemyFactory.h"
#include "BulletFactory.h"

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

    _world->getb2World()->SetContactListener(new EnemyContactListener);
    _world->getb2World()->SetContactListener(new PlayerContactListener);

    //World->debugDraw();
    
    //auto floor = b2Sprite::create("pinky.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 0.0, 0.0);
    //auto wallL = b2Sprite::create("pinky.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 0.0, 0.0);
    //auto wallR = b2Sprite::create("pinky.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 0.0, 0.0);
    //auto ceil = b2Sprite::create("pinky.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 0.0, 0.0);
    tileMapInit();

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

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::mousePressed, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    scheduleUpdate();
    //schedule(schedule_selector(MainScene::removeSomePlayer), 2.5f);
    schedule(schedule_selector(MainScene::createSomeEnemy), 0.5f);

    return true;
}

void MainScene::mousePressed(cocos2d::Event* event) {
    EventMouse* mouse = dynamic_cast<EventMouse*>(event);

    if (mouse->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

        _player->setAnimState(eAnimState::Attack);
        if (_player->canAttack(0)) {

            _player->resetAttackColldown();

            Vec2 pos = _player->getPosition();

            auto click = mouse->getLocation();

            auto director = Director::getInstance();

            Vec2 clickPos = Camera::getDefaultCamera()->getPosition() - Vec2{ director->getVisibleSize() / 2 };
            clickPos += click;

            clickPos.y = Director::getInstance()->getVisibleSize().height - click.y + Director::getInstance()->getVisibleOrigin().y;

            Vec2 dest =  clickPos - pos;
            dest.normalize();
            dest *= _player->BULLET_SPEED;

            auto bullet = BulletFactory::getInstance()->createBullet(eBulletType::playerOrdinary, _world, pos, dest);

            bullets.push_back(bullet);
        }
    }
}

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    _player->keyPressed(keyCode, event);
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    _player->KeyReleased(keyCode, event);
}

void MainScene::update(float dt) {
    _player->canAttack(dt);
    _player->move();
    _player->jump();

    for (auto i : bullets) {
        i->update(dt);
        if (i->getMoveTime() <= 0) {
            _world->removeChild(i);
        }
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](Bullet* x) { return (x->getMoveTime() <= 0); }),
        bullets.end());

    _world->update(dt);
    _world->removeIsDeletingChildren();
    _cameraTarget->setPosition(_player->getPosition().x, Director::getInstance()->getVisibleSize().height/2);
}

//UNDONE
//������! �������� ����������
static int id = 0;
void MainScene::createSomeEnemy(float dt) {
    id++;
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

