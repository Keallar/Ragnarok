#include "TileMapManager.h"

TileMapManager::TileMapManager() {
	CCTMXTiledMap* _tiledMap = new CCTMXTiledMap();
}

TileMapManager::~TileMapManager() {
	delete _tiledMap;
	delete _background;
	delete _foreground;
	delete _collidableObj;
	delete _objects;
}

TileMapManager* TileMapManager::createTileMap() {
	TileMapManager* TileMapObj = new (std::nothrow) TileMapManager();
	return TileMapObj;
}

CCTMXLayer* TileMapManager::getLayer(const std::string& layerName) {
	if (layerName == "BG")
		return _background;

	else if (layerName == "FG")
		return _foreground;

	else if (layerName == "CO")
		return _collidableObj;

	else if (layerName == "OB")
		return _objects;
	return nullptr;
}

CCTMXTiledMap* TileMapManager::getTiledMap() {
	return _tiledMap;
}

void TileMapManager::setTiledMap(const std::string& filename) {
	_tiledMap->initWithTMXFile(filename);
}

void TileMapManager::setLayer(CCTMXLayer* layer, const std::string& filename) {
	CCASSERT(!layer, "Nullptr layer");
	if (layer) {
		layer = _tiledMap->getLayer(filename);
	}
}

void TileMapManager::TileMapLayerInit(Node* node, CCTMXLayer* layer) {
	Sprite* tile = new Sprite;
	for (float i = 0; i < layer->getLayerSize().width; i++) {
		for (float j = 0; j < layer->getLayerSize().height; j++)
		{
			if (layer->getTileAt({ i, j })) {
				auto _b2test = b2Sprite::create();
				_b2test->initWithSprite(layer->getTileAt({ i, j }));
				_b2test->initBody(b2BodyType::b2_staticBody);
				node->addChild(_b2test);
				_b2test->setPosition(i * layer->getTileAt({ i, j })->getTextureRect().size.width,
					(_tiledMap->getMapSize().height - j) * layer->getTileAt({ i, j })->getTextureRect().size.height);
			}
		}
	}
}

void TileMapManager::TileMapObjectLayerInit(Node* node, CCTMXLayer* layer) {

}