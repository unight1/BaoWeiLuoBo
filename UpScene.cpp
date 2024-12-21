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

    // 背景
    auto background = Sprite::create("shengji.png");
    background->setPosition(Vec2(650, 400));
    this->addChild(background);

    // 金额标签
    auto background1 = Sprite::create("qian.png"); // 设置钱包背景
    background1->setPosition(Vec2(100, 650)); // 设置钱包位置
    this->addChild(background1);

    // 显示 money 数量的 Label
    m_moneyLabel = Label::createWithTTF("      " + std::to_string(player.getMoney()), "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 650));
    this->addChild(m_moneyLabel);

    startmoneyLabel = Label::createWithTTF("             startmoney: " + std::to_string(player.getStartmoney()), "fonts/Marker Felt.ttf", 32);
    startmoneyLabel->setPosition(Vec2(1000, 630));
    this->addChild(startmoneyLabel);

    startHPLabel = Label::createWithTTF("       startHP: " + std::to_string(player.getStartHP()), "fonts/Marker Felt.ttf", 32);
    startHPLabel->setPosition(Vec2(1000, 430));
    this->addChild(startHPLabel);

    // 第一项物品升级按钮
    auto item1Button = MenuItemImage::create("skill1.png", "skill1.png", CC_CALLBACK_1(UpScene::onItem1Button, this));
    item1Button->setPosition(Vec2(850, 550));

    // 第二项物品升级按钮
    auto item2Button = MenuItemImage::create("skill2.png", "skill2.png", CC_CALLBACK_1(UpScene::onItem2Button, this));
    item2Button->setPosition(Vec2(850, 350));

    // 返回按钮
    auto backButton = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(UpScene::onBackButton, this));
    backButton->setPosition(Vec2(70, 760));

    auto menu = Menu::create(item1Button, item2Button, backButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void UpScene::onItem1Button(Ref* sender)
{
    int money = player.getMoney();
    if (player.getStartmoney() < 800) {
        if (money >= 100)
        {
            player.consumeMoney(100);
            m_moneyLabel->setString("       " + std::to_string(player.getMoney()));

            // 升级第一项物品
            player.upgradeStartmoney();
            int item1Level = player.getStartmoney();
            startmoneyLabel->setString("             startmoney: " + std::to_string(item1Level));
        }      
    }
}

void UpScene::onItem2Button(Ref* sender)
{
    int money = player.getMoney();
    if (player.getStartHP() < 20) {
        if (money >= 100)
        {
            player.consumeMoney(100);
            m_moneyLabel->setString("       " + std::to_string(player.getMoney()));

            // 升级第二项物品
            player.upgradeStartHP();
            int item2Level = player.getStartHP();
            startHPLabel->setString("       startHP: " + std::to_string(item2Level));
        }

    }
}

void UpScene::onBackButton(Ref* sender)
{
    m_levelScene->updateButtonState();
    Director::getInstance()->popScene();
}
