#pragma once
#include "cocos2d.h"

class MainMenu : public cocos2d::Scene {
public:
	bool init() override;



	CREATE_FUNC(MainMenu);
private:

	void createMainScene();

};

class SplashScene : public cocos2d::Scene {
public:
	bool init() override;
	void update(float dt) override;

	CREATE_FUNC(SplashScene);
private:

};