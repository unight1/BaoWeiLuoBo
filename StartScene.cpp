#include "StartScene.h"
#include "Setting.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//创建场景
Scene* StartScene::createScene()
{
    return StartScene::create();
}

//打印错误信息
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //添加背景
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // 设置背景位置为屏幕中心
    background->setScale(1.5);
    this->addChild(background, 0); // 将背景添加到场景中，层级为0

    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);

    //加入菜单按钮
    auto start = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(StartScene::menuSelectLevel, this));
    auto end = MenuItemImage::create("end.png", "end.png", CC_CALLBACK_1(StartScene::menuCloseCallback, this));
    auto setting = MenuItemImage::create("set.png", "set.png", CC_CALLBACK_1(StartScene::menuSetting, this));

    // 创建菜单
    auto menu = Menu::create(start, end, setting, nullptr);
    menu->alignItemsVertically(); // 垂直排列菜单项
    this->addChild(menu, 1);

    return true;
}

//退出程序
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}



//跳转到选关界面
void StartScene::menuSelectLevel(cocos2d::Ref* pSender)
{
    auto levelSelectingScene = LevelScene::create();
    Director::getInstance()->pushScene(levelSelectingScene);
}


//进入设置界面
void StartScene::menuSetting(Ref* pSender)
{
    auto settingScene = SettingScene::create();
    Director::getInstance()->pushScene(settingScene);
}
