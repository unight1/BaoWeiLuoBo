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


    //�Ѷȵ���
    auto dif = Sprite::create("difficulty.png");
    dif->setPosition(Vec2(480, 400));
    dif->setScale(0.6f);
    this->addChild(dif);
    
    // ����������
    auto difficultySlider = ui::Slider::create();
    difficultySlider->loadBarTexture("Slider_Back.png");
    difficultySlider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "");
    difficultySlider->loadProgressBarTexture("Slider_PressBar.png");
    difficultySlider->setPosition(Vec2(680, 400));
    difficultySlider->setPercent(player.getDifficulty()); 
    difficultySlider->addEventListener(CC_CALLBACK_2(SettingScene::sliderEvent, this)); // ����¼�����
    this->addChild(difficultySlider);


    return true;
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
