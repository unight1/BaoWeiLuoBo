#include "StartScene.h"
#include "Setting.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


//ȫ�ֱ���

bool _SOUND_IS_OPEN_ = 1;              //�����Ƿ��


//��������
Scene* StartScene::createScene()
{
    return StartScene::create();
}

//��ӡ������Ϣ
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

    //��ӱ���
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // ���ñ���λ��Ϊ��Ļ����
    background->setScale(1.5);
    this->addChild(background, 0); // ��������ӵ������У��㼶Ϊ0

    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);

    //����˵���ť
    auto start = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(StartScene::menuSelectLevel, this));
    auto end = MenuItemImage::create("end.png", "end.png", CC_CALLBACK_1(StartScene::menuCloseCallback, this));
    auto setting = MenuItemImage::create("set.png", "set.png", CC_CALLBACK_1(StartScene::menuSetting, this));

    // �����˵�
    auto menu = Menu::create(start, end, setting, nullptr);
    menu->alignItemsVertically(); // ��ֱ���в˵���
    this->addChild(menu, 1);

    return true;
}

//�˳�����
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}



//��ת��ѡ�ؽ���
void StartScene::menuSelectLevel(cocos2d::Ref* pSender)
{
    auto levelSelectingScene = LevelScene::create();
    Director::getInstance()->pushScene(levelSelectingScene);
}


//�������ý���
void StartScene::menuSetting(Ref* pSender)
{
    auto settingScene = SettingScene::create();
    Director::getInstance()->pushScene(settingScene);
}
