#ifndef __UP_SCENE_H__
#define __UP_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class LevelScene;
class UpScene : public Scene
{
public:
    static UpScene* create(LevelScene* levelScene);
    Label* m_upgrade1Label;
    Label* m_upgrade2Label;
    virtual bool init(LevelScene* levelScene);
    void onItem1Button(Ref* sender);
    void onItem2Button(Ref* sender);
    Label* m_item1LevelLabel;
    Label* m_item2LevelLabel;
private:

    void onBackButton(Ref* sender);

    LevelScene* m_levelScene;
    Label* m_moneyLabel;
};

#endif // __UP_SCENE_H__