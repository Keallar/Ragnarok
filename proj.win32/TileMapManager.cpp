#include "TileMapManager.h"

TileMapManager::TileMapManager() {

}

TileMapManager::~TileMapManager() {
	delete _tiledMap;
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
}

void TileMapManager::addLayer(std::string installableName, const std::string& layerNameInMap) {
	if (_tiledMap->getLayer(layerNameInMap)) {
		_layers.push_back(std::make_pair(installableName, _tiledMap->layerNamed(layerNameInMap)));
	}
}

void TileMapManager::TileMapStaticLayerInit(Node* node, CCTMXLayer* layer) {
	Sprite* tile = new Sprite;
	for (float i = 0; i < layer->getLayerSize().width; i++) {
		for (float j = 0; j < layer->getLayerSize().height; j++){
			if (layer->getTileAt({ i, j })) {
				tile = layer->getTileAt({ i, j });
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

void TileMapManager::CollidableLayerInit(Node* node, CCTMXLayer* layer) {
	bool isTileFirst = true;
	Vec2 startPoint;
	auto _b2test = b2Sprite::create();
	for (float i = 0; i < layer->getLayerSize().height; i++) {
		for (float j = 0; j < layer->getLayerSize().width; j++){
			if (layer->getTileAt({ j, i })) {
				if (isTileFirst) {
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
					_b2test->setTiles(layer->getTileAt({ j-1, i })->getTextureRect().size.width);
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
	Sprite* tile = new Sprite;
	for (float i = 0; i < layer->getLayerSize().width; i++) {
		for (float j = 0; j < layer->getLayerSize().height; j++)
		{
			if (layer->getTileAt({ i, j })) {
				tile->create();
				tile = layer->getTileAt({ i, j });
				node->addChild(tile);
				tile->setPosition(i * layer->getTileAt({ i, j })->getTextureRect().size.width,
					(_tiledMap->getMapSize().height - j) * layer->getTileAt({ i, j })->getTextureRect().size.height);
			}
		}
	}
}

void TileMapManager::TileMapObjectLayerInit(Node* node, CCTMXLayer* layer) {

}