#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOverScreen : public cocos2d::Node {
public:
	void createLabel();

	CREATE_FUNC(GameOverScreen);
private:
	cocos2d::DrawNode* _background;
	cocos2d::Label* _text;
	cocos2d::ui::Button _button;
};

