#pragma once
#include "box2d/b2dSprite.h"
#include <vector>
class TileMapManager : public b2Sprite
{
private:
    CCTMXTiledMap* _tiledMap = new CCTMXTiledMap();
    std::vector <std::pair<std::string, CCTMXLayer*>> _layers;
public:
    TileMapManager();
    ~TileMapManager();
    static TileMapManager* createTileMap();
    CCTMXTiledMap* getTiledMap();
    CCTMXLayer* getLayerByName(const std::string& layerName);
    void setTiledMap(const std::string& filename);
    void addLayer(const std::string installableName, const std::string& layerNameInMap);
    void TileMapLayerInit(Node* node, CCTMXLayer* layer, b2BodyType bodyType);
    void TileMapObjectLayerInit(Node* node, CCTMXLayer* layer);
};

