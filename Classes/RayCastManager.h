#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "box2d/b2dRootWorldNode.h"
#include <map>
#include "Player.h"
class RayCastManager
{
private:
	std::map <std::string, int> callbackNameToNumber = {
		{"SA", 0},
		{"SM", 1},
		{"LL", 2},
		{"LD", 3}
	};
public:
	void castAllRaysOfTileMapManager(std::vector <std::vector<std::string>>& _callbackTypeProperty, std::vector <std::pair<b2Vec2, b2Vec2>>& _rays, b2WorldNode* _world, Player* _player);
};

class CallbackForSpawn : public b2RayCastCallback
{
private:
	bool isActive = false;
public:
	virtual ~CallbackForSpawn() {}

	bool getIsActive();

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction) override;
};

class CallbackForLoadLevel {};