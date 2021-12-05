#include "Trigger.h"
#include "MainScene.h"

void Trigger::onCollision() {
	auto scene = dynamic_cast<MainScene*>(getParent());
	auto _player = scene->getPlayer();
	auto _TMM = scene->getTMM();

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