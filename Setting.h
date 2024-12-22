#pragma once

#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PlayerInf.h"

class SettingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //初始化
    virtual bool init();

    //改变难度
    void sliderEvent(Ref* sender, cocos2d::ui::Slider::EventType type);

    //返回标题界面
    void goBack(cocos2d::Ref* pSender);
    

    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);
};

#endif