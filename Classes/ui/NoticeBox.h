#include "cocos2d.h"

class NoticeBox : public cocos2d::Node {
public:
	void printText(cocos2d::Label* text);

	CREATE_FUNC(NoticeBox);
private:
	cocos2d::Sprite* _paper;
};