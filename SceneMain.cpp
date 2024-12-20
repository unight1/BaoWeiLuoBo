#include "SceneBase.h"
#include "SceneMain.h"
#include "Obstacle.h"
#include "Monster.h"
#include "Tower.h"
#include "Carrot.h"
#include "TowerPosition.h"
#include "ui/CocosGUI.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC; //using namespace cocos2d

Scene1* Scene1::createScene(int level, LevelScene* levelScene)
{
    Scene1* scene = new Scene1();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

// 打印有用的错误消息，而不是在文件不存在时段错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Scene1::initMonster(int choose)
{
    if (choose == 1)
    {
        Sheep* Monster = Sheep::create();
        Monster->setPosition(Vec2(200 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 2)
    {
        Bird* Monster = Bird::create();
        Monster->setPosition(Vec2(200 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 3)
    {
        Star* Monster = Star::create();
        Monster->setPosition(Vec2(200 + 50, 500 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
}

// on "init" you need to initialize your instance
bool Scene1::init(int level, LevelScene* levelScene)
{
    do {
        CC_BREAK_IF(!SceneBase::init(level, levelScene));
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("level-1.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("level-1.mp3", true);

        moneyScene = 500 + 100 * (levelScene->getItem1Level());
        m_level = level;
        m_levelScene = levelScene; // 保存关卡选择场景的指针
        // 创建 Label，并设置字体、字号和初始文本内容

        int number = moneyScene; // 要显示的数字
        std::string text = std::to_string(number); // 将数字转换为字符串
        m_lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
        m_lable->setPosition(Vec2(150, 750));
        this->addChild(m_lable, 1);

        std::string mapName = "L1.tmx";
        initScene(mapName);

        path = {
            cocos2d::Vec2(200 + 50, 200 + 50),
            cocos2d::Vec2(500 + 50, 200 + 50),
            cocos2d::Vec2(500 + 50, 500 + 50),
            cocos2d::Vec2(800 + 50, 500 + 50),
            cocos2d::Vec2(800 + 50, 300 + 50),
            cocos2d::Vec2(700 + 50, 300 + 50),
            cocos2d::Vec2(700 + 50, 100 + 50),
            cocos2d::Vec2(1000 + 50, 100 + 50),
            cocos2d::Vec2(1000 + 50, 500 + 50),
        };

        auto create1 = CallFunc::create([=]() {initMonster(1); });
        auto create2 = CallFunc::create([=]() {initMonster(2); });
        auto create3 = CallFunc::create([=]() {initMonster(3); });

        Sprite* gameProgress = Sprite::create("gege1.png");    //创建进度条
        gameProgress->setPosition(Vec2(420, 730));
        do {
            // 创建一个空的动画对象
            auto animation = Animation::create();
            // 添加动画帧
            for (int i = 1; i <= 5; i++) {
                char filename[100];
                sprintf(filename, "gege%d.png", i);
                auto frame = SpriteFrame::create(filename, Rect(0, 0, 120, 120));
                animation->addSpriteFrame(frame);
            }

            // 设置动画属性
            animation->setDelayPerUnit(0.2f);
            animation->setLoops(100000000);

            // 创建动画动作对象
            auto animate = Animate::create(animation);

            // 将动画动作应用到精灵上
            gameProgress->runAction(Spawn::create(animate, nullptr));

            gameProgress->runAction(cocos2d::MoveBy::create(70, Vec2(400, 0)));
            this->addChild(gameProgress, 4);

        } while (0);

        runAction(Sequence::create(
            DelayTime::create(2), create1,
            DelayTime::create(2), create2,
            DelayTime::create(2), create1,
            DelayTime::create(2), create1,

            DelayTime::create(12), create2,
            DelayTime::create(2), create1,
            DelayTime::create(2), create2,
            DelayTime::create(2), create1,
            DelayTime::create(2), create1,

            DelayTime::create(12), create1,
            DelayTime::create(2), create1,
            DelayTime::create(2), create2,
            DelayTime::create(2), create1,
            DelayTime::create(2), create2,
            DelayTime::create(1), create1,


            CallFunc::create([=]() {monsterFlag = true; }),
            nullptr));

        return true;

    } while (0);
}

Scene2* Scene2::createScene(int level, LevelScene* levelScene)
{
    Scene2* scene = new Scene2();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

void Scene2::initMonster(int choose)
{
    if (choose == 1)
    {
        Sheep* Monster = Sheep::create();
        Monster->setPosition(Vec2(100 + 50, 300 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 2)
    {
        Bird* Monster = Bird::create();
        Monster->setPosition(Vec2(100 + 50, 300 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 3)
    {
        Star* Monster = Star::create();
        Monster->setPosition(Vec2(100 + 50, 300 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
}

bool Scene2::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!SceneBase::init(level, levelScene))
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("level-2.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("level-2.mp3", true);

    moneyScene = 700 + 100 * (levelScene->getItem1Level());
    m_level = level;
    m_levelScene = levelScene; // 保存关卡选择场景的指针

    // 创建 Label，并设置字体、字号和初始文本内容
    int number = moneyScene; // 要显示的数字
    std::string text = std::to_string(number); // 将数字转换为字符串
    m_lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    m_lable->setPosition(Vec2(150, 750));
    this->addChild(m_lable, 1);

    std::string mapName = "L2.tmx";
    initScene(mapName);

    path = {
    cocos2d::Vec2(300 + 50, 300 + 50),
    cocos2d::Vec2(300 + 50, 200 + 50),
    cocos2d::Vec2(600 + 50, 200 + 50),
    cocos2d::Vec2(600 + 50, 100 + 50),
    cocos2d::Vec2(800 + 50, 100 + 50),
    cocos2d::Vec2(800 + 50, 400 + 50),
    cocos2d::Vec2(900 + 50, 400 + 50),
    cocos2d::Vec2(900 + 50, 500 + 50),
    cocos2d::Vec2(1100 + 50, 500 + 50),
    cocos2d::Vec2(1150 + 50, 550 + 50),
    };

    auto create1 = CallFunc::create([=]() {initMonster(1); });
    auto create3 = CallFunc::create([=]() {initMonster(2); });
    auto create2 = CallFunc::create([=]() {initMonster(3); });

    Sprite* gameProgress = Sprite::create("gege1.png");    //创建进度条
    gameProgress->setPosition(Vec2(420, 730));
    do {
        // 创建一个空的动画对象
        auto animation = Animation::create();
        // 添加动画帧
        for (int i = 1; i <= 5; i++) {
            char filename[100];
            sprintf(filename, "gege%d.png", i);
            auto frame = SpriteFrame::create(filename, Rect(0, 0, 120, 120));
            animation->addSpriteFrame(frame);
        }

        // 设置动画属性
        animation->setDelayPerUnit(0.2f);
        animation->setLoops(100000000);

        // 创建动画动作对象
        auto animate = Animate::create(animation);

        // 将动画动作应用到精灵上
        gameProgress->runAction(Spawn::create(animate, nullptr));

        gameProgress->runAction(cocos2d::MoveBy::create(70, Vec2(400, 0)));
        this->addChild(gameProgress, 4);

    } while (0);

    runAction(Sequence::create(
        DelayTime::create(2), create1,
        DelayTime::create(2), create3,
        DelayTime::create(2), create1,
        DelayTime::create(2), create1,

        DelayTime::create(12), create2,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,
        DelayTime::create(2), create1,
        DelayTime::create(2), create1,

        DelayTime::create(12), create1,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,

        DelayTime::create(12), create1,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,
        DelayTime::create(2), create3,
        DelayTime::create(2), create2,
        DelayTime::create(1), create1,
        CallFunc::create([=]() {monsterFlag = true; }),
        nullptr));

    return true;
}

Scene3* Scene3::createScene(int level, LevelScene* levelScene)
{
    Scene3* scene = new Scene3();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

void Scene3::initMonster(int choose)    //1-3在上方出生点，4-6在下方出生点
{
    if (choose == 1)
    {
        Sheep* Monster = Sheep::create();
        Monster->setPosition(Vec2(1000, 200 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 2)
    {
        Bird* Monster = Bird::create();
        Monster->setPosition(Vec2(1000, 200 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 3)
    {
        Star* Monster = Star::create();
        Monster->setPosition(Vec2(1000, 200 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path);
    }
    else if (choose == 4)
    {
        Boss* Monster = Boss::create();
        Monster->setPosition(Vec2(1000, 200 + 50));
        this->addChild(Monster);
        Monster->moveToSequence(path1);
    }

}

// on "init" you need to initialize your instance
bool Scene3::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!SceneBase::init(level, levelScene))
    {
        return false;
    }

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("level-3.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("level-3.mp3", true);

    moneyScene = 1000 + 100 * (levelScene->getItem1Level());
    m_level = level;
    m_levelScene = levelScene; // 保存关卡选择场景的指针

    std::string mapName = "L3.tmx";
    initScene(mapName);

    // 创建 Label，并设置字体、字号和初始文本内容
    int number = moneyScene; // 要显示的数字
    std::string text = std::to_string(number); // 将数字转换为字符串
    m_lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    m_lable->setPosition(Vec2(150, 750));
    this->addChild(m_lable, 1);

    path = {
    cocos2d::Vec2(400 + 50, 200 + 50),
    cocos2d::Vec2(400 + 50, 400 + 75),
    cocos2d::Vec2(200 + 50, 400 + 75),
    cocos2d::Vec2(200 + 50, 500 + 75),
    cocos2d::Vec2(900 + 50, 500 + 75),
    cocos2d::Vec2(900 + 50, 400 + 75),
    cocos2d::Vec2(1100 + 50, 400 + 75),
    cocos2d::Vec2(1100 + 50, 82 + 50)
    };

    path1 = {
    cocos2d::Vec2(1100 + 50, 200 + 50),
    cocos2d::Vec2(1100 + 50, 82 + 50)
    };

    Sprite* gameProgress = Sprite::create("gege1.png");    //创建进度条
    gameProgress->setPosition(Vec2(420, 730));
    do {
        // 创建一个空的动画对象
        auto animation = Animation::create();
        // 添加动画帧
        for (int i = 1; i <= 5; i++) {
            char filename[100];
            sprintf(filename, "gege%d.png", i);
            auto frame = SpriteFrame::create(filename, Rect(0, 0, 120, 120));
            animation->addSpriteFrame(frame);
        }

        // 设置动画属性
        animation->setDelayPerUnit(0.2f);
        animation->setLoops(100000000);

        // 创建动画动作对象
        auto animate = Animate::create(animation);

        // 将动画动作应用到精灵上
        gameProgress->runAction(Spawn::create(animate, nullptr));

        gameProgress->runAction(cocos2d::MoveBy::create(70, Vec2(400, 0)));
        this->addChild(gameProgress, 4);

    } while (0);

    auto create1 = CallFunc::create([=]() {initMonster(1); });
    auto create2 = CallFunc::create([=]() {initMonster(2); });
    auto create3 = CallFunc::create([=]() {initMonster(3); });
    auto createBoss = CallFunc::create([=]() {initMonster(4); });

    runAction(Sequence::create(
        DelayTime::create(2), createBoss,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,

        DelayTime::create(2), create1,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,

        DelayTime::create(2), create1,
        DelayTime::create(2), create1,

        DelayTime::create(2), create1,
        DelayTime::create(2), create1,
        DelayTime::create(2), create2,

        CallFunc::create([=]() {monsterFlag = true; }),
        nullptr));
    return true;
}