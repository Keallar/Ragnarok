#include "TileMapManager.h"
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "box2d/b2dRootWorldNode.h"
#include "RayCastManager.h"
#include <string>

void RayCastManager::castAllRaysOfTileMapManager(std::vector <std::vector<std::string>> &_callbackTypeProperty, std::vector <std::pair<b2Vec2, b2Vec2>> &_rays, b2WorldNode* _world) {
	for (int i = 0; i < _rays.size(); i++) {
		int currentElementSize = _callbackTypeProperty[i].size();
		for (int j = 0; j < currentElementSize; j++) {
			std::string someSum;
			someSum.push_back(_callbackTypeProperty.at(i).at(j).at(0));
			someSum.push_back(_callbackTypeProperty.at(i).at(j).at(1));
			switch (callbackNameToNumber.at(someSum)) {
			case 0:
				
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				break;
			}
		}
	}
}

