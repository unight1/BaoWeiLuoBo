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
    bool m_unlockedLevels[3];
    int m_unlockedLevel1;
    int m_unlockedLevel2;
    int m_unlockedLevel3;
    void selectLevel1(Ref* sender);
    void selectLevel2(Ref* sender);
    void selectLevel3(Ref* sender);
    void LevelScene::goBack(Ref* pSender);
    int m_unlockLevel;// 淇濆瓨宸茶В閿佺殑鍏冲崱缂栧彿

    MenuItemImage* m_level1Button;
    MenuItemImage* m_level2Button;
    MenuItemImage* m_level3Button;
    void updateButtonState();
    //Sprite* m_gameImage; // mubu
    Label* m_moneyLabel;//鏄剧ず閽�
    void consumeMoney(int n);//鑺遍挶
    int getMoney();//杩斿洖閽�
    void enterUpgradeScene(Ref* sender);
    void upgradeItem1();//鑾峰彇鎶�鑳界瓑绾т笌杩斿洖
    void upgradeItem2();
    int getItem1Level();
    int getItem2Level();
    CREATE_FUNC(LevelScene);
    void clear(Ref* sender);//娓呯┖璁板綍
private:
    int money;//灞�澶栬揣甯�
    int skill1 = 0;//鎶�鑳界瓑绾�
    int skill2 = 0;
    Scene* m_gameScene; // 淇濆瓨 GameScene 鍦烘櫙鐨勬寚閽�
};

#endif // __LEVEL_SCENE_H__

