#pragma once
#include "cocos2d.h"
#include "NoticeBox.h"

USING_NS_CC;

void NoticeBox::printText(std::string text) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _paper = Sprite::create("images/paper.png");
    //_paper->initWithFile("paper.png");
    //_paper->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    _paper->setPosition({origin.x, origin.y});

    Vec2 a = _paper->getPosition();
    _textLabel = Label::create();
    _textLabel->setString(text);
    TTFConfig textConfig;
    textConfig.fontFilePath = "fonts/arial.ttf";
    textConfig.fontSize = 18;
    _textLabel->setTTFConfig(textConfig);

    _paper->setScale(_textLabel->getContentSize().width / 160, _textLabel->getContentSize().height / 180);

    addChild(_paper);

    _textLabel->setPosition({ origin.x, origin.y});
    Vec2 b = _textLabel->getPosition();
    addChild(_textLabel);
}
//func for remove all, helped to reduce GL calls, but GL calls leak is exist

void NoticeBox::cleanPaper() {
    removeChild(_paper);
    removeChild(_textLabel);
}

Vec2 NoticeBox::getSize() {
    return { _paper->getContentSize().width * _paper->getScaleX(),  _paper->getContentSize().height * _paper->getScaleY() };
}