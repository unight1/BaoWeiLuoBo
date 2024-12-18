#pragma once

#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    //��ʼ��
    virtual bool init();

    //�˳�����
    void menuCloseCallback(cocos2d::Ref* pSender);

    //��ת��ѡ�ؽ���
    void menuSelectLevel(cocos2d::Ref* pSender);

    //�������ý���
    void menuSetting(cocos2d::Ref* pSender);

    CREATE_FUNC(StartScene);
};

#endif