#include "cocos2d.h"


class HUD : public cocos2d::Node {
public:
    void beginLife(int hp, int mana);
    void setHp(int hp);
    void setMana(int mana);
    void showPers();
    CREATE_FUNC(HUD);
private:
    int _hp;
    int _mana;
    cocos2d::Label* hpChange;
    cocos2d::Sprite* hpImgBase;
    cocos2d::Sprite* hpImgLife;
    cocos2d::Label* text;
    cocos2d::Sprite* imgManaBase;
    cocos2d::Sprite* imgMana;
};