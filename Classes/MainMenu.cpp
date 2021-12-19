#include "MainMenu.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"

#include "imgui/CCIMGUIGLViewImpl.h"
#include "imgui/CCImGuiLayer.h"
#include "imgui/CCIMGUI.h"

USING_NS_CC;


bool MainMenu::init() {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto background = Sprite::create("MainTitle.png");
	background->setPosition(origin + background->getContentSize()/2);
	addChild(background);

	auto start = ui::Button::create("startButton.png");

	start->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			createMainScene();
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	addChild(start);
	start->setPosition(origin + visibleSize / 2);

	auto options = ui::Button::create("optionsButton.png");
	addChild(options);
	options->setPosition(start->getPosition() - Vec2(0, options->getContentSize().height + 20));

	auto exit = ui::Button::create("exitButton.png");
	addChild(exit);
	exit->setPosition(options->getPosition() - Vec2(0, options->getContentSize().height + 20));

	exit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->end();
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
		});

	scheduleUpdate();

	return true;
}

void MainMenu::createMainScene() {
	auto splash = SplashScene::create();

	Director::getInstance()->replaceScene(splash);
}

bool SplashScene::init() {
	auto loading = Sprite::create("Loading.png");
	loading->setPosition(Director::getInstance()->getVisibleOrigin() + loading->getContentSize()/2);
	addChild(loading);

	scheduleUpdate();
	return true;
}

void SplashScene::update(float dt) {
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(scene);

	Director::getInstance()->getScheduler()->schedule([=](float dt)
		{
			auto runningScene = Director::getInstance()->getRunningScene();
			if (runningScene && !runningScene->getChildByName("ImGUILayer"))
			{
				runningScene->addChild(ImGuiLayer::create(), INT_MAX, "ImGUILayer");
			}
		}, this, 0, false, "checkIMGUI");
}