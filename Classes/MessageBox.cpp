#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MessageBox.h"

USING_NS_CC;

void MessageBox::printText(cocos2d::Label* text) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    paper = Sprite::create();
    paper->initWithFile("paper.png");
    paper->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    paper->setScale(text->getContentSize().width / 160, text->getContentSize().height / 180);

    addChild(paper);

    text->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    addChild(text);
}