#include "Setting.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


extern bool _SOUND_IS_OPEN_;



//��������
Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

//��ӡ������Ϣ
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

    //���ӱ���
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // ���ñ���λ��Ϊ��Ļ����
    background->setScale(1.5);
    this->addChild(background, 0); // ���������ӵ������У��㼶Ϊ0



    //���ؼ�
    auto back = ui::Button::create("exit.png", "exit.png");
    back->setPosition(Vec2(400, 600));
    back->addClickEventListener(CC_CALLBACK_1(SettingScene::goBack, this));
    this->addChild(back);


    //��������

    auto music_switch = Sprite::create("music_switch.png");
    music_switch->setPosition(Vec2(480,450)); 
    music_switch->setScale(0.6f);
    this->addChild(music_switch); 

    auto volumeCheckBox = ui::CheckBox::create("checkbox_normal.png", "checkbox_selected.png");
    volumeCheckBox->setPosition(Vec2(580,450)); // ���ø�ѡ��λ��
    volumeCheckBox->addEventListener(CC_CALLBACK_2(SettingScene::checkBoxEvent, this)); // �����¼�����
    this->addChild(volumeCheckBox);
    const bool isChecked = UserDefault::getInstance()->getBoolForKey("VolumeCheckBoxState",true); // Ĭ��ֵΪ true
    volumeCheckBox->setSelected(isChecked); // ���ø�ѡ��״̬




    return true;
}


//��������
void SettingScene::checkBoxEvent(Ref* sender, ui::CheckBox::EventType type) 
{
    _SOUND_IS_OPEN_ = !_SOUND_IS_OPEN_;
    if (_SOUND_IS_OPEN_)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGMusic.mp3", true);
        UserDefault::getInstance()->setBoolForKey("VolumeCheckBoxState", true);
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey("VolumeCheckBoxState", false);
    }
}



//���ر������
void SettingScene::goBack(Ref* pSender)
{
    Director::getInstance()->popScene();
}