#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class LevelScene : public Scene
{
public:
    static LevelScene* create();
    void unlockLevel(int level);
    virtual bool init();
    bool m_unlockedLevels[3];
    int m_unlockedLevel1;
    int m_unlockedLevel2 ;
    int m_unlockedLevel3 ;
    void selectLevel1(Ref* sender);
    void selectLevel2(Ref* sender);
    void selectLevel3(Ref* sender);
    int m_unlockLevel ;// 保存已解锁的关卡编号
    MenuItemImage* m_level1Button;
    MenuItemImage* m_level2Button;
    MenuItemImage* m_level3Button;
    void updateButtonState();
    Sprite* m_gameImage; // mubu
    Label* m_moneyLabel;//显示钱
    void consumeMoney(int n);//花钱
    int getMoney();//返回钱
    void enterUpgradeScene(Ref* sender);
    void upgradeItem1();//获取技能等级与返回
    void upgradeItem2();
    int getItem1Level();
    int getItem2Level();
private:
    int money;//局外货币
    int skill1 = 0;//技能等级
    int skill2 = 0;
    Scene* m_gameScene; // 保存 GameScene 场景的指针
};

#endif // __LEVEL_SCENE_H__