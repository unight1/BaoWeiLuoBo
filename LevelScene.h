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
    int m_unlockLevel ;// �����ѽ����Ĺؿ����
    MenuItemImage* m_level1Button;
    MenuItemImage* m_level2Button;
    MenuItemImage* m_level3Button;
    void updateButtonState();
    Sprite* m_gameImage; // mubu
    Label* m_moneyLabel;//��ʾǮ
    void consumeMoney(int n);//��Ǯ
    int getMoney();//����Ǯ
    void enterUpgradeScene(Ref* sender);
    void upgradeItem1();//��ȡ���ܵȼ��뷵��
    void upgradeItem2();
    int getItem1Level();
    int getItem2Level();
private:
    int money;//�������
    int skill1 = 0;//���ܵȼ�
    int skill2 = 0;
    Scene* m_gameScene; // ���� GameScene ������ָ��
};

#endif // __LEVEL_SCENE_H__