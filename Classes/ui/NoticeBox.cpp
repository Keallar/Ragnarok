#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NoticeBox.h"

USING_NS_CC;

void NoticeBox::printText(cocos2d::Label* text) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _paper = Sprite::create();
    _paper->initWithFile("paper.png");
    _paper->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    _paper->setScale(text->getContentSize().width / 160, text->getContentSize().height / 180);

    addChild(_paper);

    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    addChild(text);
}