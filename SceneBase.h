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

    // 虚析构
    virtual ~SceneBase() {};

    virtual bool init(int level, LevelScene* levelScene);

    virtual void initMonster(int choose) {};    //初始化怪物或障碍物，choose选择初始化哪种怪物或障碍物

    void setButton(bool flag);   // 游戏完成时调用的放置按钮函数，为true获胜，为false失败

    void setPauseButton();       //放置暂停按钮

    void pauseOperate();         //暂停操作

    void continueOperate();      //继续游戏

    void setMenuButton();        //放置菜单按钮

    void onGameMenu();           //菜单界面

    void continueGame();         //继续游戏

    void goBack();               //返回

    void initScene(std::string& mapname);   
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);

    void createBottle(Ref* sender);     //放置瓶子炮塔

    void createFire(Ref* sender);  //放置火焰秒杀炮塔

    void createStar(Ref* sender);       //放置星星炮塔

    void createSunflower(Ref* sender);  //放置太阳花炮塔

    void createShit(Ref* sender);  //放置屎塔

    void onGameWin();

    void onGameFail();

    void update(float delta);

    void addMoney(int money);

    void updateMoney(int money);

    int moneyScene;                     //场景中的的钱

    Carrot* getCarrot()const { return carrot; }

protected:
    Label* m_lable;                     //显示当前金钱
    bool monsterFlag = false;           //怪物是否生成完毕的标志，true为生成完毕
    float time = 0.0f;                  //游戏的持续时间
    std::vector<Vec2> path;             //移动路径
    int m_level;                        //保存当前的关卡编号
    LevelScene* m_levelScene;           //保存关卡选择场景的指针
    Carrot* carrot=Carrot::create();    //指向萝卜的唯一实例
    Label* waveLabel;                   //波次显示
};

#endif  //__SCENCEBASE_SCENE_H__

