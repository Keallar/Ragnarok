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

CCTMXLayer* TileMapManager::getLayer(const std::string& layerName) {
	if (layerName == "BG")
		return _background;

	else if (layerName == "FG")
		return _foreground;

	else if (layerName == "CO")
		return _collidableObj;

	else if (layerName == "OB")
		return _objects;

	else
		return nullptr;
}

CCTMXTiledMap* TileMapManager::getTiledMap() {
	return _tiledMap;
}

void TileMapManager::setTiledMap(const std::string& filename) {
	_tiledMap->initWithTMXFile(filename);
}

void TileMapManager::setLayer(CCTMXLayer* layer, const std::string& filename) {
	if (layer) {
		layer = _tiledMap->getLayer(filename);
	}
	else
	{

	}
}

void TileMapManager::TileMapLayerInit(Node& node, CCTMXLayer* layer) {

}

void TileMapManager::TileMapObjectLayerInit(Node& node, CCTMXLayer* layer) {

}