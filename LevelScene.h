#pragma once

#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PlayerInf.h"

USING_NS_CC;
class LevelScene : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    void selectLevel1(Ref* sender);
    void selectLevel2(Ref* sender);
    void selectLevel3(Ref* sender);
    void unlockLevel(int level);
    void goBack(Ref* pSender);
    MenuItemImage* m_level1Button;
    MenuItemImage* m_level2Button;
    MenuItemImage* m_level3Button;
    void updateButtonState();
    //Sprite* m_gameImage; // mubu
    Label* m_moneyLabel;//显示钱
    void enterUpgradeScene(Ref* sender);
    void clear(Ref* sender);
    CREATE_FUNC(LevelScene);
    
private:
    Scene* m_gameScene; // 保存 GameScene 场景的指针
};

#endif // __LEVEL_SCENE_H__