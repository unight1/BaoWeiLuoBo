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


    //音量开关

    auto music_switch = Sprite::create("music_switch.png");
    music_switch->setPosition(Vec2(480,450)); 
    music_switch->setScale(0.6f);
    this->addChild(music_switch); 

    auto volumeCheckBox = ui::CheckBox::create("checkbox_normal.png", "checkbox_selected.png");
    volumeCheckBox->setPosition(Vec2(580,450)); // 设置复选框位置
    volumeCheckBox->addEventListener(CC_CALLBACK_2(SettingScene::checkBoxEvent, this)); // 添加事件监听
    this->addChild(volumeCheckBox);
    
    volumeCheckBox->setSelected(player.getMusic()); // 设置复选框状态

    


    return true;
}


//开关音量
void SettingScene::checkBoxEvent(Ref* sender, ui::CheckBox::EventType type) 
{
    player.changeMusic();
    player.save();
}


//返回标题界面
void SettingScene::goBack(Ref* pSender)
{
    Director::getInstance()->popScene();
}
