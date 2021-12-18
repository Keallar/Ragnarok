#include "Trigger.h"
#include "MainScene.h"

Trigger::~Trigger() {

}

void Trigger::onCollision() {

	auto scene = dynamic_cast<MainScene*>(getParent()->getParent());
	auto _player = scene->getPlayer();
	auto _TMM = scene->getTMM();

	std::string _someStr;
	_someStr.push_back(triggerFunc.at(0));
	_someStr.push_back(triggerFunc.at(1));

	std::string FG = "FG";
	switch (callbackNameToNumber.at(_someStr))
	{
	case 0:
		isActivated = true;
		_player->setPosition({ 8000, 25000 });
		break;
	case 1:
		isActivated = true;
		break;
	case 2:
		isActivated = true;
		triggerFunc.erase(0,2);
		_TMM->getTiledMap()->getLayer(FG + triggerFunc)->setVisible(true);
		break;
	case 3:
		isActivated = true;
		triggerFunc.erase(0, 2);
		_TMM->getTiledMap()->getLayer(FG + triggerFunc)->setVisible(false);
		break;
	case 4:
		if (_player->getJumpState() == eJumpState::Fall || _player->getJumpState() == eJumpState::None) {
			_player->getBody()->ApplyLinearImpulseToCenter({ 0, 20 }, true);
		}
		_player->changeHp(-10);
		break;
	}
}

void Trigger::setIsActive(bool dt) {
	isActivated = dt;
}

bool Trigger::getIsActive() {
	return isActivated;
}

void Trigger::setTriggerFunc(std::string someStr) {
	triggerFunc = someStr;
}

Trigger* Trigger::create()
{
	Trigger* trigger = new (std::nothrow) Trigger();
	if (trigger && trigger->init())
	{
		trigger->initBody(b2BodyType::b2_kinematicBody);
		trigger->autorelease();
		return trigger;
	}
	CC_SAFE_DELETE(trigger);
	return nullptr;
}