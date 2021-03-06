#include "TileMapManager.h"
#include "box2d/b2dRootWorldNode.h"
#include <iostream>
#include "Trigger.h"
#include "box2d/b2dSprite.h"
#include "MainScene.h"

TileMapManager::TileMapManager() {

}

TileMapManager::~TileMapManager() {
	delete _tiledMap;
}

std::vector<std::vector<std::string>> TileMapManager::getCallbacks() {
	return _callbackTypeProperty;
}

std::vector <std::pair<b2Vec2, b2Vec2>>  TileMapManager::getRays() {
	return _rays;
}

TileMapManager* TileMapManager::createTileMap() {
	TileMapManager* TileMapObj = new (std::nothrow) TileMapManager();
	return TileMapObj;
}

CCTMXLayer* TileMapManager::getLayerByName(const std::string& layerName) {
	for (std::pair<std::string, CCTMXLayer*> _pair : _layers) {
		if (_pair.first == layerName)
			return _pair.second;
	}
	return nullptr;
}

CCTMXTiledMap* TileMapManager::getTiledMap() {
	return _tiledMap;
}

void TileMapManager::setTiledMap(const std::string& filename) {
	_tiledMap->initWithTMXFile(filename);
	_tiledMap->setPosition(0, 32);
}

void TileMapManager::addLayer(std::string installableName, const std::string& layerNameInMap) {
	if (_tiledMap->getLayer(layerNameInMap)) {
		_layers.push_back(std::make_pair(installableName, _tiledMap->layerNamed(layerNameInMap)));
	}
}


void TileMapManager::CollidableLayerInit(Node* node, CCTMXLayer* layer) {
	bool isTileFirst = true;
	Vec2 startPoint;
	auto _b2test = b2Sprite::create();
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::platform);
	filter.maskBits = static_cast<uint16>(eColMask::platform);
	layer->setVisible(false);
	for (float i = 0; i < layer->getLayerSize().height; i++) {
		for (float j = 0; j < layer->getLayerSize().width; j++){
			if (layer->getTileAt({ j, i })) {
				if (isTileFirst) {
					_b2test->setVisible(false);
					_b2test->initWithSprite(layer->getTileAt({ j, i }));
					startPoint.set({ j,i });
					isTileFirst = false;
					_b2test->setAnchorPoint({0, 0.5});
				}
				else {
					_b2test->setContentSize({ _b2test->getContentSize().width + layer->getTileAt({ j - 1, i })->getTextureRect().size.width,
											_b2test->getContentSize().height });
				}
			}
			else {
				if (_b2test->getContentSize().width) {
					_b2test->initBody(b2BodyType::b2_staticBody);
					_b2test->setTiles(layer->getTileAt({ j - 1, i })->getTextureRect().size.width, node);
					_b2test->getFixtureDef()->filter = filter;
					node->addChild(_b2test);
					_b2test->setPosition(startPoint.x * layer->getTileAt({ j-1, i })->getTextureRect().size.width,
						(_tiledMap->getMapSize().height - startPoint.y) * layer->getTileAt({ j-1, i })->getTextureRect().size.width );
				}
				_b2test = b2Sprite::create();
				isTileFirst = true;
			}

		}
	}

}

void TileMapManager::TileMapBackgroundLayerInit(Node* node, CCTMXLayer* layer) {
	/*for (float i = 0; i < layer->getLayerSize().width; i++) {
		for (float j = 0; j < layer->getLayerSize().height; j++)
		{
			if (layer->getTileAt({ i, j })) {
				Sprite* tile = new Sprite;
				tile->createWithTexture(layer->getTileAt({ i, j })->getTexture());
				node->addChild(tile);
				tile->setPosition(i * 64,
					(_tiledMap->getMapSize().height - j) * 64);
			}
		}
	}*/
	//???????? ???????? ?? ?? ????
}

void TileMapManager::TileMapObjectLayerInit(b2WorldNode* _world) {
	auto scene = dynamic_cast<MainScene*>(_world->getParent());
	CCTMXObjectGroup* firstGroup = _tiledMap->getObjectGroup("ObjectLayer");
	b2Filter filter;
	filter.categoryBits = static_cast<uint16>(eColCategory::trigger);
	filter.maskBits = static_cast<uint16>(eColMask::trigger);
	auto objects = firstGroup->getObjects();
	auto _trigger = Trigger::create();
	auto _tileSize = _tiledMap->getTileSize().width;
	for (auto obj : objects) {
		//Some variables
		auto objMap = obj.asValueMap();
		float x = objMap.at("x").asFloat();
		float y = objMap.at("y").asFloat();
		float width = objMap.at("width").asFloat();
		float height = objMap.at("height").asFloat();

		//Callback setter
		std::string callbackProperties = objMap.at("ReturnSmth").asString();
		_trigger->setTriggerFunc(callbackProperties);
		_trigger->setAnchorPoint({ 0, 1});
		//Set trigger by size
		height *= 1 / _world->getPTM();
		width *= 1 / _world->getPTM();
		_trigger->setTrigger(width, height);

		//BitMask
		_trigger->getFixtureDef()->filter = filter;

		//Adding to scene
		_world->addChild(_trigger);
		scene->addTrigger(_trigger);

		_trigger->setPosition(x, y+_tileSize/2);
		_trigger = Trigger::create();
	}
}

void TileMapManager::testRay(b2WorldNode* _world) {
	b2Vec2 RayStart = _rays[0].first;
	b2Vec2 RayEnd = _rays[0].second;
	DefaultCallback* callback = new DefaultCallback;
	_world->getb2World()->RayCast(callback, RayStart, RayEnd);
}

float32 DefaultCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
	const b2Vec2& normal, float32 fraction)
{
	std::cout<<"callback works";
	
	return 0;
}