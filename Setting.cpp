#include "Setting.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "LevelScene.h"


USING_NS_CC;


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

    //��ӱ���
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // ���ñ���λ��Ϊ��Ļ����
    background->setScale(1.5);
    this->addChild(background, 0); // ��������ӵ������У��㼶Ϊ0



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
    volumeCheckBox->addEventListener(CC_CALLBACK_2(SettingScene::checkBoxEvent, this)); // ����¼�����
    this->addChild(volumeCheckBox);    
    volumeCheckBox->setSelected(player.getMusic()); // ���ø�ѡ��״̬

    //�Ѷȵ���
    auto dif = Sprite::create("difficulty.png");
    dif->setPosition(Vec2(480, 350));
    dif->setScale(0.6f);
    this->addChild(dif);
    
    // ����������
    auto difficultySlider = ui::Slider::create();
    difficultySlider->loadBarTexture("Slider_Back.png");
    difficultySlider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "");
    difficultySlider->loadProgressBarTexture("Slider_PressBar.png");
    difficultySlider->setPosition(Vec2(680, 350));
    difficultySlider->setPercent(player.getDifficulty()); 
    difficultySlider->addEventListener(CC_CALLBACK_2(SettingScene::sliderEvent, this)); // ����¼�����
    this->addChild(difficultySlider);


    return true;
}


//��������
void SettingScene::checkBoxEvent(Ref* sender, ui::CheckBox::EventType type) 
{
    player.changeMusic();
    player.save();
}

//�ı��Ѷ�
void SettingScene::sliderEvent(Ref* sender, ui::Slider::EventType type)
{
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<ui::Slider*>(sender);
        int percent = slider->getPercent();
        player.changeDifficulty(percent);
    }
}


//���ر������
void SettingScene::goBack(Ref* pSender)
{
    Director::getInstance()->popScene();
}
