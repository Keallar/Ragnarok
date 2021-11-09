#include "cocos2d.h"


class UI : public cocos2d::Node {
public:
    void beginLife(int hp);
    void beginMana(int mana);
    void setHp(int hp);
    void setMana(int mana);
    void printText(cocos2d::Label* text);
    void showPers();
    CREATE_FUNC(UI);
private:
    int _hp;
    int _mana;
    cocos2d::Label* hpChange;
    cocos2d::Sprite* hpImgBase;
    cocos2d::Sprite* hpImgLife;
    cocos2d::Label* text;
    cocos2d::Sprite* imgManaBase;
    cocos2d::Sprite* imgMana;
    cocos2d::Sprite* paper;
};