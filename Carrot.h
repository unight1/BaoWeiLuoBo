
#ifndef __CARROT_H__
#define __CARROT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class Carrot : public Sprite
{
private:
    int HP;                             //血量
    int MaxHP;                          //最大血量
    Vec2 Position;                      //位置
    Sprite* carrot;                     //萝卜精灵
    Sprite* carrot_HP;                  //血量精灵
    Label* carrotHP;                    //血量数值

public:
    CREATE_FUNC(Carrot);

    void takeDamage(int damage);        //造成伤害

    void setCarrotPosition(Vec2 pos);   //设置萝卜的位置

    void putCarrot(int hp);                   //放置萝卜

    Vec2 getCarrotPosition() const;     //获取萝卜的位置

    bool isAlive();                     //是否存活

    bool init() override;               // 初始化

};

#endif // __CARROT_H__