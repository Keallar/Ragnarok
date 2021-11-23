#include "cocos2d.h"

class MessageBox : public cocos2d::Node {
public:
	cocos2d::Sprite* paper;
	void printText(cocos2d::Label* text);
};