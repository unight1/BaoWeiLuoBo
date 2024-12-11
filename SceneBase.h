#ifndef __SCENCEBASE_SCENE_H__
#define __SCENCEBASE_SCENE_H__

#include "LevelScene.h"
#include "cocos2d.h"
#include "Target.h"

USING_NS_CC; //using namespace cocos2d

class SceneBase : public cocos2d::Scene
{
public:
    static SceneBase* createScene(int level, LevelScene* levelScene);

    // ������
    virtual ~SceneBase() {};

    virtual bool init(int level, LevelScene* levelScene);

    virtual void initMonster(int choose) {};    //��ʼ�����chooseѡ���ʼ�����ֹ���

    void takeCarrotDamage(int damage);

    void setButton(bool flag);   // ��Ϸ���ʱ���õķ��ð�ť������Ϊtrue��ʤ��Ϊfalseʧ��

    void setPauseButton();       //������ͣ��ť

    void pauseOperate();         //��ͣ����

    void continueOperate();      //������Ϸ

    void setMenuButton();        //���ò˵���ť

    void onGameMenu();           //�˵�����

    void continueGame();         //������Ϸ

    void goBack();               //����

    cocos2d::Vec2 getCarrotPosition() const;

    void setCarrotPosition(cocos2d::Vec2 position);

    void initScene(std::string& mapname);   
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void createBottle(cocos2d::Ref* sender);     //����ƿ������

    void createStar(cocos2d::Ref* sender);       //������������

    void createSunflower(cocos2d::Ref* sender);  //����̫��������

    void onGameWin();

    void onGameFail();

    void update(float delta);

    void addMoney(int money);

    void updateMoney(int money);

    int moneyScene;                     //�����еĵ�Ǯ
protected:
    cocos2d::Label* m_lable;            //��ʾ��ǰ��Ǯ
    bool monsterFlag = false;           //�����Ƿ�������ϵı�־��trueΪ�������
    float time = 0.0f;                  //��Ϸ�ĳ���ʱ��
    Sprite* m_carrot;                   //ָ���ܲ���ָ��
    cocos2d::Label* m_carrotHP;         //��ʾ�ܲ���Ѫ��
    int carrotHP = 10;                  //�ܲ��ĳ�ʼѪ��
    cocos2d::Vec2 carrotPosition;       //�ܲ���λ��
    std::vector<cocos2d::Vec2> path;    //�ƶ�·��
    int m_level;                        //���浱ǰ�Ĺؿ����
    LevelScene* m_levelScene;           //����ؿ�ѡ�񳡾���ָ��
};

#endif  //__SCENCEBASE_SCENE_H__

