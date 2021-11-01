#pragma once
#include "box2d/b2dSprite.h"
class TileMapManager : public b2Sprite
{
private:
    CCTMXTiledMap* _tiledMap;
    CCTMXLayer* _background;
    CCTMXLayer* _foreground;
    CCTMXLayer* _collidableObj;
    CCTMXLayer* _objects;
public:
    TileMapManager();
    ~TileMapManager();
    CCTMXTiledMap* getTiledMap();
    CCTMXLayer* getLayer(const std::string& layerName);
    void setTiledMap(const std::string& filename);
    void setLayer(CCTMXLayer* layer, const std::string& filename);
    void TileMapLayerInit(Node &node, CCTMXLayer* layer);
    void TileMapObjectLayerInit(Node& node, CCTMXLayer* layer);
};

