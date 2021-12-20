#include "GameOverScreen.h"
USING_NS_CC;

void GameOverScreen::createLabel() {
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const Vec2 visibleSize = Director::getInstance()->getVisibleSize();

    _background = DrawNode::create();
    const Vec2 backSize = visibleSize;
    _background->drawSolidRect(origin, backSize, Color4F(0, 0, 0, 1));
    addChild(_background);
    _background->setPosition(origin);

    _text = Label::create();
    _text->setString("Restart");
    TTFConfig textConfig;
    textConfig.fontFilePath = "fonts/OptimusPrinceps.ttf";
    textConfig.fontSize = 28;
    _text->setTTFConfig(textConfig);
    _text->setPosition(origin.x + visibleSize.x / 2, origin.y + visibleSize.y / 4);
    addChild(_text);
}