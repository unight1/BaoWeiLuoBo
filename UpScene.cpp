#include "UpScene.h"
#include "LevelScene.h"


UpScene* UpScene::create(LevelScene* levelScene)
{
    UpScene* scene = new UpScene();
    if (scene && scene->init(levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}

bool UpScene::init(LevelScene* levelScene)
{
    if (!Scene::init())
    {
        return false;
    }

    m_levelScene = levelScene;

    // ����
    auto background = Sprite::create("shengji.png");
    background->setPosition(Vec2(650, 400));
    this->addChild(background);

    // ����ǩ
    auto background1 = Sprite::create("qian.png"); // ����Ǯ������
    background1->setPosition(Vec2(100, 650)); // ����Ǯ��λ��
    this->addChild(background1);

    // ��ʾ money ������ Label
    m_moneyLabel = Label::createWithTTF("      " + std::to_string(m_levelScene->getMoney()), "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 650));
    this->addChild(m_moneyLabel);

    m_item1LevelLabel = Label::createWithTTF("Level " + std::to_string(m_levelScene->getItem1Level()), "fonts/Marker Felt.ttf", 32);
    m_item1LevelLabel->setPosition(Vec2(1000, 630));
    this->addChild(m_item1LevelLabel);

    m_item2LevelLabel = Label::createWithTTF("Level " + std::to_string(m_levelScene->getItem2Level()), "fonts/Marker Felt.ttf", 32);
    m_item2LevelLabel->setPosition(Vec2(1000, 430));
    this->addChild(m_item2LevelLabel);

    // ��һ����Ʒ������ť
    auto item1Button = MenuItemImage::create("skill1.png", "skill1.png", CC_CALLBACK_1(UpScene::onItem1Button, this));
    item1Button->setPosition(Vec2(850, 550));

    // �ڶ�����Ʒ������ť
    auto item2Button = MenuItemImage::create("skill2.png", "skill2.png", CC_CALLBACK_1(UpScene::onItem2Button, this));
    item2Button->setPosition(Vec2(850, 350));

    // ���ذ�ť
    auto backButton = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(UpScene::onBackButton, this));
    backButton->setPosition(Vec2(70, 760));

    auto menu = Menu::create(item1Button, item2Button, backButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void UpScene::onItem1Button(Ref* sender)
{
    int money = m_levelScene->getMoney();
    if (m_levelScene->getItem1Level() < 3) {
        if (money >= 100)
        {
            m_levelScene->consumeMoney(100);
            m_moneyLabel->setString("       " + std::to_string(m_levelScene->getMoney()));

            // ������һ����Ʒ
            m_levelScene->upgradeItem1();
            int item1Level = m_levelScene->getItem1Level();
            m_item1LevelLabel->setString("Level " + std::to_string(item1Level));
        }      
    }
}

void UpScene::onItem2Button(Ref* sender)
{
    int money = m_levelScene->getMoney();
    if (m_levelScene->getItem2Level() < 3) {
        if (money >= 100)
        {
            m_levelScene->consumeMoney(100);
            m_moneyLabel->setString("       " + std::to_string(m_levelScene->getMoney()));

            // �����ڶ�����Ʒ
            m_levelScene->upgradeItem2();
            int item2Level = m_levelScene->getItem2Level();
            m_item2LevelLabel->setString("Level " + std::to_string(item2Level));
        }

    }
}

void UpScene::onBackButton(Ref* sender)
{
    m_levelScene->updateButtonState();
    Director::getInstance()->popScene();
}
