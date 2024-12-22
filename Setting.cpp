#include "Setting.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "LevelScene.h"


USING_NS_CC;


//创建场景
Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

//打印错误信息
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SettingScene::init()
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


    //返回键
    auto back = ui::Button::create("exit.png", "exit.png");
    back->setPosition(Vec2(400, 600));
    back->addClickEventListener(CC_CALLBACK_1(SettingScene::goBack, this));
    this->addChild(back);


    //难度调节
    auto dif = Sprite::create("difficulty.png");
    dif->setPosition(Vec2(480, 400));
    dif->setScale(0.6f);
    this->addChild(dif);
    
    // 创建进度条
    auto difficultySlider = ui::Slider::create();
    difficultySlider->loadBarTexture("Slider_Back.png");
    difficultySlider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "");
    difficultySlider->loadProgressBarTexture("Slider_PressBar.png");
    difficultySlider->setPosition(Vec2(680, 400));
    difficultySlider->setPercent(player.getDifficulty()); 
    difficultySlider->addEventListener(CC_CALLBACK_2(SettingScene::sliderEvent, this)); // 添加事件监听
    this->addChild(difficultySlider);


    return true;
}




//改变难度
void SettingScene::sliderEvent(Ref* sender, ui::Slider::EventType type)
{
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<ui::Slider*>(sender);
        int percent = slider->getPercent();
        player.changeDifficulty(percent);
    }
}


//返回标题界面
void SettingScene::goBack(Ref* pSender)
{
    Director::getInstance()->popScene();
}
