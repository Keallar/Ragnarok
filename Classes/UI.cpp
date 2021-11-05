#define __MyProject__MyScene__
#define ACTION_PLAY 1

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "UI.h"
USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void UI::beginLife() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    hp = 100;
    /*hpChange = Label::createWithTTF(std::to_string(hp), "fonts/Marker Felt.ttf", 24);
    if (!hpChange) {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else {
        hpChange->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - hpChange->getContentSize().height));

        addChild(hpChange, 1);
    }*/



    hpImgBase = Sprite::create();
    hpImgBase->initWithFile("hpBase.png");
    addChild(hpImgBase);
    hpImgBase->setPosition(Vec2(origin.x + hpImgBase->getContentSize().width / 2, origin.y + visibleSize.height - hpImgBase->getContentSize().height / 2));


    hpImgLife = Sprite::create();
    hpImgLife->initWithFile("hpLife.png");
    addChild(hpImgLife);
    hpImgLife->setPosition(Vec2(origin.x + hpImgLife->getContentSize().width / 2, origin.y + visibleSize.height - hpImgLife->getContentSize().height / 2));



    ui::Button* btnPlus = ui::Button::create();
    btnPlus->setTitleText("Life+");
    btnPlus->setPosition(Vec2(visibleSize.height / 2, visibleSize.width / 2));

    btnPlus->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (hp < 100) {
                hp++;
            }
            /*hpChange->setString(std::to_string(hp));*/

            hpImgLife->setScale((hpImgLife->getContentSize().width / 400) * ((float)hp / 100), hpImgLife->getContentSize().height / 13);
            hpImgLife->setPosition(Vec2(hpImgLife->getContentSize().width / 2 - ((hpImgLife->getContentSize().width) * ((100 - hp) / 100.f)) / 2,
                Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - hpImgLife->getContentSize().height / 2));
            break;
        default:
            break;
        }
        });

    addChild(btnPlus);

    ui::Button* btnMinus = ui::Button::create();
    btnMinus->setTitleText("Life-");
    btnMinus->setPosition(Vec2(visibleSize.height / 2, visibleSize.width / 4));

    btnMinus->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (hp > 1) {
                hp--;
            }
            /*hpChange->setString(std::to_string(hp));*/


            hpImgLife->setScale((hpImgLife->getContentSize().width / 400) * ((float)hp / 100), hpImgLife->getContentSize().height / 13);
            hpImgLife->setPosition(Vec2(hpImgLife->getContentSize().width / 2 - ((hpImgLife->getContentSize().width) * ((100 - hp) / 100.f)) / 2,
                Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - hpImgLife->getContentSize().height / 2));
            break;
        default:
            break;
        }
        });

    addChild(btnMinus);
}

void UI::beginMana() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    mana = 100;
    imgManaBase = Sprite::create();
    imgManaBase->initWithFile("hpBase.png");
    addChild(imgManaBase);
    hpImgBase->setPosition(Vec2(origin.x + imgManaBase->getContentSize().width / 2, origin.y + visibleSize.height - imgManaBase->getContentSize().height / 2 - hpImgBase->getContentSize().height));

    imgMana = Sprite::create();
    imgMana->initWithFile("Mana.png");
    addChild(imgMana);
    imgMana->setPosition(Vec2(origin.x + imgMana->getContentSize().width / 2, origin.y + visibleSize.height - imgMana->getContentSize().height / 2 - hpImgBase->getContentSize().height));

    ui::Button* btnPlus = ui::Button::create();
    btnPlus->setTitleText("Mana+");
    btnPlus->setPosition(Vec2(visibleSize.height / 2 + 100, visibleSize.width / 2));

    btnPlus->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (mana < 100) {
                mana++;
            }
            
            imgMana->setScale((imgMana->getContentSize().width / 400) * ((float)mana / 100), imgMana->getContentSize().height / 13);
            imgMana->setPosition(Vec2(imgMana->getContentSize().width / 2 - ((imgMana->getContentSize().width) * ((100 - mana) / 100.f)) / 2,
                Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - imgMana->getContentSize().height / 2 - hpImgBase->getContentSize().height));
            break;
        default:
            break;
        }
        });

    addChild(btnPlus);

    ui::Button* btnMinus = ui::Button::create();
    btnMinus->setTitleText("Mana-");
    btnMinus->setPosition(Vec2(visibleSize.height / 2 + 100, visibleSize.width / 4));

    btnMinus->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (mana > 1) {
                mana--;
            }
            
            imgMana->setScale((imgMana->getContentSize().width / 400) * ((float)mana / 100), imgMana->getContentSize().height / 13);
            imgMana->setPosition(Vec2(imgMana->getContentSize().width / 2 - ((imgMana->getContentSize().width) * ((100 - mana) / 100.f)) / 2,
                Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height - imgMana->getContentSize().height / 2 - hpImgBase->getContentSize().height));
            break;
        default:
            break;
        }
        });

    addChild(btnMinus);
}


