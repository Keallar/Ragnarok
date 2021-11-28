#pragma once
#include "box2d/b2dSprite.h"
#include <vector>
#include "Box2D/Dynamics/b2WorldCallbacks.h"
class TileMapManager : public b2Sprite
{
private:
    CCTMXTiledMap* _tiledMap = new CCTMXTiledMap();
    std::vector <std::pair<std::string, CCTMXLayer*>> _layers;
    std::vector <std::pair<b2Vec2, b2Vec2>> _rays;
public:
    TileMapManager();
    ~TileMapManager();
    static TileMapManager* createTileMap();
    CCTMXTiledMap* getTiledMap();
    CCTMXLayer* getLayerByName(const std::string& layerName);
    void setTiledMap(const std::string& filename);
    void addLayer(const std::string installableName, const std::string& layerNameInMap);
    void TileMapObjectLayerInit(b2WorldNode* _world);
    void TileMapBackgroundLayerInit(Node* node, CCTMXLayer* layer);
    void CollidableLayerInit(Node* node, CCTMXLayer* layer);
    void testRay(b2WorldNode* _world);  
};

class DefaultCallback : public b2RayCastCallback
{
public:
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, float32 fraction) override;
};