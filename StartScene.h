#pragma once

#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //初始化
    virtual bool init();

    //退出程序
    void menuCloseCallback(cocos2d::Ref* pSender);

    //跳转到选关界面
    void menuSelectLevel(cocos2d::Ref* pSender);

    //进入设置界面
    void menuSetting(cocos2d::Ref* pSender);

    CREATE_FUNC(StartScene);
};

#endif