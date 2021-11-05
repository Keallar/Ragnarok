#include "cocos2d.h"


class UI : public cocos2d::Scene
{
public:
    int hp;
    cocos2d::Label* hpChange;
    cocos2d::Sprite* hpImgBase;
    cocos2d::Sprite* hpImgLife;
    void beginLife();

    int mana;
    cocos2d::Sprite* imgManaBase;
    cocos2d::Sprite* imgMana;
    void beginMana();

    void printText(Label* text);

    CREATE_FUNC(UI);

};