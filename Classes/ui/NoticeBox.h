#include "cocos2d.h"

class NoticeBox : public cocos2d::Node {
public:
	void printText(std::string text);
	void cleanPaper();
	void addTouchEvent();
	cocos2d::Vec2 getSize();

	CREATE_FUNC(NoticeBox);
private:
	cocos2d::Sprite* _paper;
	cocos2d::Label* _textLabel;
};