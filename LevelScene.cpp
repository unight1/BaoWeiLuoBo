#include "StartScene.h"
#include "LevelScene.h"
#include "SceneMain.h"
#include "UpScene.h"
#include "audio/include/SimpleAudioEngine.h"

extern bool _SOUND_IS_OPEN_;

Scene* LevelScene::createScene()
{
    return LevelScene::create();
}

bool LevelScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ���ر��������
    money = UserDefault::getInstance()->getIntegerForKey("Money", 0);
    m_unlockLevel = UserDefault::getInstance()->getIntegerForKey("UnlockedLevel", 1); // Ĭ�Ͻ�����һ��
    skill1 = UserDefault::getInstance()->getIntegerForKey("Skill1Level", 0);
    skill2 = UserDefault::getInstance()->getIntegerForKey("Skill2Level", 0);

    // ��ӱ���
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // ���ñ���λ��Ϊ��Ļ����
    background->setScale(1.5f);
    this->addChild(background, 0); // ��������ӵ������У��㼶Ϊ0

    // ��������
    auto upgradeButton = MenuItemImage::create("upgrade.png", "upgrade.png", CC_CALLBACK_1(LevelScene::enterUpgradeScene, this));
    upgradeButton->setPosition(Vec2(1100, 100));

    // ���ؼ�
    auto backButton = ui::Button::create("exit.png", "exit.png");
    backButton->setPosition(Vec2(100, 600));
    backButton->addClickEventListener(CC_CALLBACK_1(LevelScene::goBack, this));
    this->addChild(backButton);

    // ѡ��ؿ���ť
    auto level1Button = MenuItemImage::create("game1.png", "game1.png", CC_CALLBACK_1(LevelScene::selectLevel1, this));
    auto level2Button = MenuItemImage::create("game2.png", "game2.png", CC_CALLBACK_1(LevelScene::selectLevel2, this));
    auto level3Button = MenuItemImage::create("game3.png", "game3.png", CC_CALLBACK_1(LevelScene::selectLevel3, this));
    level1Button->setPosition(Vec2(200, 400));
    level2Button->setPosition(Vec2(600, 400));
    level3Button->setPosition(Vec2(1000, 400));
    

    m_level1Button = level1Button;
    m_level2Button = level2Button;
    m_level3Button = level3Button;

    // ���ó�ʼ��ͼƬ
    m_level1Button->setNormalImage(Sprite::create("game1.png"));
    m_level2Button->setNormalImage(Sprite::create("game2.png"));
    m_level3Button->setNormalImage(Sprite::create("game3.png"));

    // ��ʾ money ������ Label
    auto background1 = Sprite::create("qian.png"); // ʹ��ָ����ͼƬ�ļ����� Sprite ������Ϊ����
    background1->setPosition(Vec2(100, 700)); 
    this->addChild(background1);

    m_moneyLabel = Label::createWithTTF("      0", "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 700));
    this->addChild(m_moneyLabel);

    auto menu = Menu::create(level1Button, level2Button, level3Button, upgradeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    // ��ʼ����ť״̬
    m_unlockedLevel1 = true;
    m_unlockedLevel2 = (m_unlockLevel >= 2);
    m_unlockedLevel3 = (m_unlockLevel >= 3);

    updateButtonState(); // ���°�ť״̬

    return true;
}

// ���ر������
void LevelScene::goBack(Ref* pSender)
{
    // ��������
    UserDefault::getInstance()->setIntegerForKey("Money", money);
    UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", m_unlockLevel);
    UserDefault::getInstance()->setIntegerForKey("Skill1Level", skill1);
    UserDefault::getInstance()->setIntegerForKey("Skill2Level", skill2);
    UserDefault::getInstance()->flush(); // ȷ�����ݱ�д��

    Director::getInstance()->popScene();
}

void LevelScene::selectLevel1(Ref* sender)
{

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    m_gameScene = Scene1::createScene(1, this); // ���ݹؿ����
    Director::getInstance()->pushScene(m_gameScene);
}

void LevelScene::selectLevel2(Ref* sender)
{
    if (m_unlockLevel >= 2) // ����ڶ����ѽ���
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene2::createScene(2, this); // ���ݹؿ���ź� LevelScene ������ָ��
        Director::getInstance()->pushScene(m_gameScene);
    }
}

void LevelScene::selectLevel3(Ref* sender)
{
    if (m_unlockedLevel3) // ����������ѽ���
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene3::createScene(3, this); // ���ݹؿ���ź� LevelScene ������ָ��
        Director::getInstance()->pushScene(m_gameScene);
    }
}

void LevelScene::updateButtonState()
{
    m_moneyLabel->setString("       " + std::to_string(money));
    if (m_unlockedLevel2)
    {
        m_level2Button->setNormalImage(Sprite::create("game2.png")); // �������ͼƬ
    }
    else
    {
        m_level2Button->setNormalImage(Sprite::create("game2_locked.png")); // δ������ͼƬ
    }

    if (m_unlockedLevel3)
    {
        m_level3Button->setNormalImage(Sprite::create("game3.png")); // �������ͼƬ
    }
    else
    {
        m_level3Button->setNormalImage(Sprite::create("game3_locked.png")); // δ������ͼƬ
    }
}

void LevelScene::unlockLevel(int level)
{
    m_unlockLevel = level;

    if (level == 2)
    {
        m_unlockedLevel2 = true;
    }
    else if (level == 3)
    {
        m_unlockedLevel3 = true;
    }

    updateButtonState(); // ���°�ť״̬��ͼƬ
}

void LevelScene::consumeMoney(int n) {
    money = money - n;
}

int LevelScene::getMoney() {
    return money;
}

void LevelScene::enterUpgradeScene(Ref* sender)
{
    auto scene = UpScene::create(this);
    Director::getInstance()->pushScene(scene);
}

// ����1����
void LevelScene::upgradeItem1() {
    skill1 += 1;
}

// ����2����
void LevelScene::upgradeItem2() {
    skill2 += 1;
}

// ���ؼ���1�ȼ�
int LevelScene::getItem1Level() {
    return skill1;
}

// ���ؼ���2�ȼ�
int LevelScene::getItem2Level() {
    return skill2;
}