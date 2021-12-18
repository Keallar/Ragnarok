#include "cocos2d.h"

class NoticeBox : public cocos2d::Node {
public:
	void printText(std::string text);
	void cleanPaper();
	void addTouchEvent();

	CREATE_FUNC(NoticeBox);
private:
	cocos2d::Sprite* _paper;
	cocos2d::Label* _textLabel;
};