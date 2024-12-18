#pragma once

#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class SettingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //初始化
    virtual bool init();

    //开关音量
    void SettingScene::checkBoxEvent(Ref* sender, cocos2d::ui::CheckBox::EventType type);


    //返回标题界面
    void goBack(cocos2d::Ref* pSender);
    

    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);
};

#endif