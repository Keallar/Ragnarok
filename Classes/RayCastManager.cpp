#include "TileMapManager.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "box2d/b2dRootWorldNode.h"
#include "RayCastManager.h"
#include <string>

void RayCastManager::castAllRaysOfTileMapManager(
	std::vector <std::vector<std::string>> &_callbackTypeProperty, 
	std::vector <std::pair<b2Vec2, b2Vec2>> &_rays, 
	b2WorldNode* _world, 
	Player* _player, 
	CCTMXTiledMap* _tiledMap) {
	std::string FG = "FG";
	for (int i = 0; i < _rays.size(); i++) {
		int currentElementSize = _callbackTypeProperty[i].size();
		CallbackForSpawn* callback = new CallbackForSpawn;
		for (int j = 0; j < currentElementSize; j++) {
			std::string someSum;
			someSum.push_back(_callbackTypeProperty.at(i).at(j).at(0));
			someSum.push_back(_callbackTypeProperty.at(i).at(j).at(1));
			switch (callbackNameToNumber.at(someSum)) {
			case 0:
				_world->getb2World()->RayCast(callback, _rays[i].first, _rays[i].second);
				if (callback->getIsActive()) {
					_player->setPosition({8000, 25000}); //UNDONE SPAWNPOINT
					callback->setIsActive(false);
				}
				break;
			case 1:
				_world->getb2World()->RayCast(callback, _rays[i].first, _rays[i].second);
				//UNDONE enemy creation
				break;
			case 2:
				_world->getb2World()->RayCast(callback, _rays[i].first, _rays[i].second);
				if (callback->getIsActive()) {
					_tiledMap->getLayer(FG + _callbackTypeProperty.at(i).at(j).at(2))->setVisible(true);
				}
				break;
			case 3:
				_world->getb2World()->RayCast(callback, _rays[i].first, _rays[i].second);
				if (callback->getIsActive()) {
					_tiledMap->getLayer(FG + _callbackTypeProperty.at(i).at(j).at(2))->setVisible(false);
				}
				delete callback;
				break;
			}
		}
		//Здесь нужно сделать удаление луча если он скастился.
		delete callback;
	}
}

bool CallbackForSpawn::getIsActive() {
	return isActive;
}

float32 CallbackForSpawn::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
	const b2Vec2& normal, float32 fraction) {
	isActive = true;
	return 0;
}

void CallbackForSpawn::setIsActive(bool _activity) {
	isActive = _activity;
}