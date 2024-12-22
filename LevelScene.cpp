#include "StartScene.h"
#include "LevelScene.h"
#include "SceneMain.h"
#include "UpScene.h"
#include "audio/include/SimpleAudioEngine.h"
#include "wave.h"


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

   player.load();
    

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

    //�����ʷ��¼��
    auto clearButton = ui::Button::create("clear.png", "clear.png");
    clearButton->setPosition(Vec2(100, 100));
    clearButton->setScale(0.5f);
    clearButton->addClickEventListener(CC_CALLBACK_1(LevelScene::clear, this));
    this->addChild(clearButton);

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

    updateButtonState(); // ���°�ť״̬

    return true;
}

// ���ر������
void LevelScene::goBack(Ref* pSender)
{
    player.save();

    Director::getInstance()->popScene();
}

void LevelScene::selectLevel1(Ref* sender)
{

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    m_gameScene = Scene1::createScene(1, this); // ���ݹؿ����
    Director::getInstance()->pushScene(m_gameScene);
    game.clear();
    player.save();
}

void LevelScene::selectLevel2(Ref* sender)
{
    if (player.getLevel() >= 2) // ����ڶ����ѽ���
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene2::createScene(2, this); // ���ݹؿ���ź� LevelScene ������ָ��
        Director::getInstance()->pushScene(m_gameScene);
    }
    game.clear();
    player.save();
}

void LevelScene::selectLevel3(Ref* sender)
{
    if (player.getLevel() >= 3) // ����������ѽ���
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene3::createScene(3, this); // ���ݹؿ���ź� LevelScene ������ָ��
        Director::getInstance()->pushScene(m_gameScene);
    }
    game.clear();
    player.save();
}

void LevelScene::updateButtonState()
{
    m_moneyLabel->setString("       " + std::to_string(player.getMoney()));
    if (player.getLevel() >= 2)
    {
        m_level2Button->setNormalImage(Sprite::create("game2.png")); // �������ͼƬ
    }
    else
    {
        m_level2Button->setNormalImage(Sprite::create("game2_locked.png")); // δ������ͼƬ
    }

    if (player.getLevel() >=3)
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
    player.changeULevel(level);
    updateButtonState(); // ���°�ť״̬��ͼƬ
}


void LevelScene::enterUpgradeScene(Ref* sender)
{
    auto scene = UpScene::create(this);
    Director::getInstance()->pushScene(scene);
}


void LevelScene::clear(Ref* sender) {
    player.clear();
    updateButtonState(); // ���°�ť״̬
    Director::getInstance()->popScene();
}