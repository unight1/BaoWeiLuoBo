#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class Target : public Sprite {
public:
    // 虚析构
    virtual ~Target() {};
    // 造成伤害
    virtual void takeDamage(int damage);
    // 判断是否存活
    bool isAlive() const;
    // 设置血量
    void setHP(int HP);
    // 获取半径
    int getRadius();
    //设置集火目标
    void setAllTarget();


protected:
    int HP;  // 血量
    int maxHP; // 最大血量
    int value;// 击杀奖励
    int radius;// 半径
    ProgressTimer* Health = nullptr;// 血条的指针
    Sprite* choose;//选中精灵
    Target() {};// 受保护的构造函数
};

#endif // __TARGET_H__