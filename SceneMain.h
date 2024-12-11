#ifndef __SCENCEMAIN_SCENE_H__
#define __SCENCEMAIN_SCENE_H__

#include "SceneBase.h"

class SceneBase;
class Scene1 : public SceneBase
{
public:
    static Scene1* createScene(int level, LevelScene* levelScene);
    virtual bool init(int level, LevelScene* levelScene) override;
    virtual void initMonster(int choose) override;
    virtual ~Scene1() {};
};

class Scene2 : public SceneBase
{
public:
    static Scene2* createScene(int level, LevelScene* levelScene);
    virtual bool init(int level, LevelScene* levelScene) override;
    virtual void initMonster(int choose) override;
    // ÐéÎö¹¹
    virtual ~Scene2() {};
};

class Scene3 : public SceneBase
{
public:
    static Scene3* createScene(int level, LevelScene* levelScene);
    virtual bool init(int level, LevelScene* levelScene) override;
    virtual void initMonster(int choose) override;
    // ÐéÎö¹¹
    virtual ~Scene3() {};
protected:
    std::vector<Vec2> path1;
};
#endif // __SCENCEMAIN_SCENE_H__