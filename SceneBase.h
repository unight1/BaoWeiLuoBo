#ifndef __SCENCEBASE_SCENE_H__
#define __SCENCEBASE_SCENE_H__

#include "LevelScene.h"
#include "cocos2d.h"
#include "Target.h"
#include "Carrot.h"

USING_NS_CC; 

class SceneBase : public Scene
{
public:
    static SceneBase* createScene(int level, LevelScene* levelScene);

    // ������
    virtual ~SceneBase() {};

    virtual bool init(int level, LevelScene* levelScene);

    virtual void initMonster(int choose) {};    //��ʼ��������ϰ��chooseѡ���ʼ�����ֹ�����ϰ���

    void setButton(bool flag);   // ��Ϸ���ʱ���õķ��ð�ť������Ϊtrue��ʤ��Ϊfalseʧ��

    void setPauseButton();       //������ͣ��ť

    void pauseOperate();         //��ͣ����

    void continueOperate();      //������Ϸ

    void setMenuButton();        //���ò˵���ť

    void onGameMenu();           //�˵�����

    void continueGame();         //������Ϸ

    void goBack();               //����

    void initScene(std::string& mapname);   
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);

    void createBottle(Ref* sender);     //����ƿ������

    void createFire(Ref* sender);  //���û�����ɱ����

    void createStar(Ref* sender);       //������������

    void createSunflower(Ref* sender);  //����̫��������

    void createShit(Ref* sender);  //����ʺ��

    void onGameWin();

    void onGameFail();

    void update(float delta);

    void addMoney(int money);

    void updateMoney(int money);

    int moneyScene;                     //�����еĵ�Ǯ

    Carrot* getCarrot()const { return carrot; }

protected:
    Label* m_lable;                     //��ʾ��ǰ��Ǯ
    bool monsterFlag = false;           //�����Ƿ�������ϵı�־��trueΪ�������
    float time = 0.0f;                  //��Ϸ�ĳ���ʱ��
    std::vector<Vec2> path;             //�ƶ�·��
    int m_level;                        //���浱ǰ�Ĺؿ����
    LevelScene* m_levelScene;           //����ؿ�ѡ�񳡾���ָ��
    Carrot* carrot=Carrot::create();    //ָ���ܲ���Ψһʵ��
    Label* waveLabel;                   //������ʾ
};

#endif  //__SCENCEBASE_SCENE_H__

