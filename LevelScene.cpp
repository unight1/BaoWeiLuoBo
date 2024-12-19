#include "StartScene.h"
#include "LevelScene.h"
#include "SceneMain.h"
#include "UpScene.h"
#include "audio/include/SimpleAudioEngine.h"


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

    // 加载保存的数据
    money = UserDefault::getInstance()->getIntegerForKey("Money", 0);
    m_unlockedLevel = UserDefault::getInstance()->getIntegerForKey("UnlockedLevel", 1); // 默认解锁第一关
    skill1 = UserDefault::getInstance()->getIntegerForKey("Skill1Level", 0);
    skill2 = UserDefault::getInstance()->getIntegerForKey("Skill2Level", 0);
    

    // 添加背景
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // 设置背景位置为屏幕中心
    background->setScale(1.5f);
    this->addChild(background, 0); // 将背景添加到场景中，层级为0

    // 升级界面
    auto upgradeButton = MenuItemImage::create("upgrade.png", "upgrade.png", CC_CALLBACK_1(LevelScene::enterUpgradeScene, this));
    upgradeButton->setPosition(Vec2(1100, 100));

    // 返回键
    auto backButton = ui::Button::create("exit.png", "exit.png");
    backButton->setPosition(Vec2(100, 600));
    backButton->addClickEventListener(CC_CALLBACK_1(LevelScene::goBack, this));
    this->addChild(backButton);

    //清空历史记录键
    auto clearButton = ui::Button::create("clear.png", "clear.png");
    clearButton->setPosition(Vec2(100, 100));
    clearButton->setScale(0.5f);
    clearButton->addClickEventListener(CC_CALLBACK_1(LevelScene::clear, this));
    this->addChild(clearButton);

    // 选择关卡按钮
    auto level1Button = MenuItemImage::create("game1.png", "game1.png", CC_CALLBACK_1(LevelScene::selectLevel1, this));
    auto level2Button = MenuItemImage::create("game2.png", "game2.png", CC_CALLBACK_1(LevelScene::selectLevel2, this));
    auto level3Button = MenuItemImage::create("game3.png", "game3.png", CC_CALLBACK_1(LevelScene::selectLevel3, this));
    level1Button->setPosition(Vec2(200, 400));
    level2Button->setPosition(Vec2(600, 400));
    level3Button->setPosition(Vec2(1000, 400));
    m_level1Button = level1Button;
    m_level2Button = level2Button;
    m_level3Button = level3Button;

    // 设置初始的图片
    m_level1Button->setNormalImage(Sprite::create("game1.png"));
    m_level2Button->setNormalImage(Sprite::create("game2.png"));
    m_level3Button->setNormalImage(Sprite::create("game3.png"));

    // 显示 money 数量的 Label
    auto background1 = Sprite::create("qian.png"); // 使用指定的图片文件创建 Sprite 对象作为背景
    background1->setPosition(Vec2(100, 700)); 
    this->addChild(background1);

    m_moneyLabel = Label::createWithTTF("      0", "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 700));
    this->addChild(m_moneyLabel);

    auto menu = Menu::create(level1Button, level2Button, level3Button, upgradeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    updateButtonState(); // 更新按钮状态

    return true;
}

// 返回标题界面
void LevelScene::goBack(Ref* pSender)
{
    save();

    Director::getInstance()->popScene();
}

void LevelScene::selectLevel1(Ref* sender)
{

    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    m_gameScene = Scene1::createScene(1, this); // 传递关卡编号
    Director::getInstance()->pushScene(m_gameScene);
    save();
}

void LevelScene::selectLevel2(Ref* sender)
{
    if (m_unlockedLevel >= 2) // 如果第二关已解锁
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene2::createScene(2, this); // 传递关卡编号和 LevelScene 场景的指针
        Director::getInstance()->pushScene(m_gameScene);
    }
    save();
}

void LevelScene::selectLevel3(Ref* sender)
{
    if (m_unlockedLevel >= 3) // 如果第三关已解锁
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene3::createScene(3, this); // 传递关卡编号和 LevelScene 场景的指针
        Director::getInstance()->pushScene(m_gameScene);
    }
    save();
}

void LevelScene::updateButtonState()
{
    m_moneyLabel->setString("       " + std::to_string(money));
    if (m_unlockedLevel>=2)
    {
        m_level2Button->setNormalImage(Sprite::create("game2.png")); // 解锁后的图片
    }
    else
    {
        m_level2Button->setNormalImage(Sprite::create("game2_locked.png")); // 未解锁的图片
    }

    if (m_unlockedLevel>=3)
    {
        m_level3Button->setNormalImage(Sprite::create("game3.png")); // 解锁后的图片
    }
    else
    {
        m_level3Button->setNormalImage(Sprite::create("game3_locked.png")); // 未解锁的图片
    }
}

void LevelScene::unlockLevel(int level)
{
    if (m_unlockedLevel < level)
        m_unlockedLevel = level;
    save();
    updateButtonState(); // 更新按钮状态和图片
}

void LevelScene::consumeMoney(int n) {
    money = money - n;
    save();
}

int LevelScene::getMoney() {
    return money;
}

void LevelScene::enterUpgradeScene(Ref* sender)
{
    auto scene = UpScene::create(this);
    Director::getInstance()->pushScene(scene);
}

// 技能1升级
void LevelScene::upgradeItem1() {
    skill1 += 1;
    save();
}

// 技能2升级
void LevelScene::upgradeItem2() {
    skill2 += 1;
    save();
}

// 返回技能1等级
int LevelScene::getItem1Level() {
    return skill1;
}

// 返回技能2等级
int LevelScene::getItem2Level() {
    return skill2;
}

//清空历史记录
void LevelScene::clear(Ref* sender) {
    // 清空保存的数据
    UserDefault::getInstance()->setIntegerForKey("Money", 0);
    UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", 1); // 重置为默认解锁第一关
    UserDefault::getInstance()->setIntegerForKey("Skill1Level", 0);
    UserDefault::getInstance()->setIntegerForKey("Skill2Level", 0);
    UserDefault::getInstance()->flush(); 

    // 更新当前数据
    money = 0;
    m_unlockedLevel = 1;
    skill1 = 0;
    skill2 = 0;

    save();

    updateButtonState(); // 更新按钮状态
    Director::getInstance()->popScene();
}

//存档
void LevelScene::save()
{
    // 保存数据
    UserDefault::getInstance()->setIntegerForKey("Money", money);
    UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", m_unlockedLevel);
    UserDefault::getInstance()->setIntegerForKey("Skill1Level", skill1);
    UserDefault::getInstance()->setIntegerForKey("Skill2Level", skill2);
    UserDefault::getInstance()->flush(); // 确保数据被写入
}