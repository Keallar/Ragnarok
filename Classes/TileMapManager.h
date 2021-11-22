#pragma once
#include "box2d/b2dSprite.h"
#include <vector>
class TileMapManager : public b2Sprite {
public:
    TileMapManager();
    ~TileMapManager();
    static TileMapManager* createTileMap();
    CCTMXTiledMap* getTiledMap();
    CCTMXLayer* getLayerByName(const std::string& layerName);
    void setTiledMap(const std::string& filename);
    void addLayer(const std::string installableName, const std::string& layerNameInMap);
    void TileMapObjectLayerInit(Node* node, CCTMXLayer* layer);
    void TileMapBackgroundLayerInit(Node* node, CCTMXLayer* layer);
    void CollidableLayerInit(Node* node, CCTMXLayer* layer);
private:
    std::vector <std::pair<std::string, CCTMXLayer*>> _layers;
    CCTMXTiledMap* _tiledMap = new CCTMXTiledMap();
};

