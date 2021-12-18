#pragma once
#include <string>
#include "box2d/b2dSprite.h"
class Trigger : public b2Sprite
{
private:
	std::map <std::string, int> callbackNameToNumber = {
		{"SA", 0},
		{"SM", 1},
		{"LL", 2},
		{"LD", 3},
		{"BF", 5}
		};
	bool isActivated = false;
	std::string triggerFunc;
public:

	~Trigger();

	static Trigger* create();
	bool getIsActive();
	void setIsActive(bool dt);

	void setTriggerFunc(std::string someStr);
	void onCollision();
};

