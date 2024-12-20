#pragma once

#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class LevelScene : public Scene
{
public:
    static Scene* createScene();
    void unlockLevel(int level);
    virtual bool init();
    void selectLevel1(Ref* sender);
    void selectLevel2(Ref* sender);
    void selectLevel3(Ref* sender);
    void LevelScene::goBack(Ref* pSender);
    int m_unlockedLevel;// 保存已解锁的关卡编号
    MenuItemImage* m_level1Button;
    MenuItemImage* m_level2Button;
    MenuItemImage* m_level3Button;
    void updateButtonState();
    //Sprite* m_gameImage; // mubu
    Label* m_moneyLabel;//显示钱
    void consumeMoney(int n);//花钱
    int getMoney();//返回钱
    void enterUpgradeScene(Ref* sender);
    void upgradeItem1();//获取技能等级与返回
    void upgradeItem2();
    int getItem1Level();
    int getItem2Level();
    CREATE_FUNC(LevelScene);
    
    void clear(Ref* sender);//清空记录

    void save();//保存记录


private:
    int money;//局外货币
    int skill1 = 0;//技能等级
    int skill2 = 0;
    Scene* m_gameScene; // 保存 GameScene 场景的指针
};

#endif // __LEVEL_SCENE_H__