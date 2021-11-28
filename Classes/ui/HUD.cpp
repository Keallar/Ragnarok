#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HUD.h"

USING_NS_CC;

static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void HUD::beginLife(int hp, int mana) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _hp = hp;
    hpImgBase = Sprite::create();
    hpImgBase->initWithFile("hpBase.png");
    hpImgBase->setPosition(Vec2(origin.x + hpImgBase->getContentSize().width / 2, origin.y + visibleSize.height - hpImgBase->getContentSize().height / 2));
    addChild(hpImgBase);

    hpImgLife = Sprite::create();
    hpImgLife->initWithFile("hpLife.png");
    hpImgLife->setPosition(Vec2(origin.x + hpImgLife->getContentSize().width / 2, origin.y + visibleSize.height - hpImgLife->getContentSize().height / 2));
    addChild(hpImgLife);

    _mana = mana;
    imgManaBase = Sprite::create();
    imgManaBase->initWithFile("hpBase.png");
    imgManaBase->setPosition(Vec2(origin.x + imgManaBase->getContentSize().width / 2, origin.y + visibleSize.height - imgManaBase->getContentSize().height / 2 - hpImgBase->getContentSize().height));
    addChild(imgManaBase);

    imgMana = Sprite::create();
    imgMana->initWithFile("Mana.png");
    imgMana->setPosition(Vec2(origin.x + imgMana->getContentSize().width / 2, origin.y + visibleSize.height - imgMana->getContentSize().height / 2 - hpImgBase->getContentSize().height));
    addChild(imgMana);
}

void HUD::showPers() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto paper = Sprite::create();
    paper->initWithFile("paper.png");
    paper->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
    paper->setScale(2, 0.4);
    addChild(paper);

    text = Label::createWithTTF("Please select one character to play", "fonts/Marker Felt.ttf", 24);
    text->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
    addChild(text);

    auto imgPers1 = ui::Button::create("pers1.png");
    imgPers1->setScale(0.3f);
    imgPers1->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 3 * 2 + origin.y));

    imgPers1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            text->setString("Name1. The one-armed god of honor \nand war.");
            
            break;
        default:
            break;
        }
        });

    addChild(imgPers1, 1);

    auto namePers1 = Label::createWithTTF("Name1", "fonts/Marker Felt.ttf", 24);
    namePers1->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 3 * 2 + origin.y + imgPers1->getContentSize().height / 5));
    addChild(namePers1);

    auto imgPers2 = ui::Button::create("pers2.png");
    imgPers2->setScale(0.2f);
    imgPers2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3 * 2 + origin.y));

    imgPers2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            text->setString("Name2. One of the aces, the god of \nspring and light.");
            
            break;
        default:
            break;
        }
        });
    addChild(imgPers2);

    auto namePers2 = Label::createWithTTF("Name2", "fonts/Marker Felt.ttf", 24);
    namePers2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3 * 2 + origin.y + imgPers2->getContentSize().height / 7.5));
    addChild(namePers2);

    auto imgPers3 = ui::Button::create("pers3.png");
    imgPers3->setScale(0.164f);
    imgPers3->setPosition(Vec2(visibleSize.width / 4 * 3 + origin.x, visibleSize.height / 3 * 2 + origin.y));

    imgPers3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            text->setString("Name3. God of vengeance and silence, \nson of Odin and the giantess Grid.");
            break;
        default:
            break;
        }
        });
    addChild(imgPers3);

    auto namePers3 = Label::createWithTTF("Name3", "fonts/Marker Felt.ttf", 24);
    namePers3->setPosition(Vec2(visibleSize.width / 4 * 3 + origin.x, visibleSize.height / 3 * 2 + origin.y + imgPers3->getContentSize().height / 9));
    addChild(namePers3);
}

void HUD::setHp(int hp) {
    _hp = hp;
    hpImgLife->setScale((hpImgLife->getContentSize().width / 400) * ((float)_hp / 100), hpImgLife->getContentSize().height / 13);
    hpImgLife->setPosition(Vec2(hpImgLife->getContentSize().width / 2 - ((hpImgLife->getContentSize().width) * ((100 - _hp) / 100.f)) / 2,
        Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - hpImgLife->getContentSize().height / 2));
}

void HUD::setMana(int mana) {
    _mana = mana;
    imgMana->setScale((imgMana->getContentSize().width / 400) * ((float)_mana / 100), imgMana->getContentSize().height / 13);
    imgMana->setPosition(Vec2(imgMana->getContentSize().width / 2 - ((imgMana->getContentSize().width) * ((100 - _mana) / 100.f)) / 2,
        Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - imgMana->getContentSize().height / 2 - hpImgBase->getContentSize().height));
}

void HUD::gameOver(bool player) {
    if (player) {
        const Vec2 origin = Director::getInstance()->getVisibleOrigin();
        DrawNode* background = DrawNode::create();
        const Vec2 backSize{ 5000, 5000 };
        background->drawSolidRect(origin - backSize, Director::getInstance()->getVisibleSize() + Size(backSize), Color4F(0, 0, 0, 1));
        addChild(background);
    }
}