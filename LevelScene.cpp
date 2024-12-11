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

    // 鍔犺浇淇濆瓨鐨勬暟鎹�
    money = UserDefault::getInstance()->getIntegerForKey("Money", 0);
    m_unlockLevel = UserDefault::getInstance()->getIntegerForKey("UnlockedLevel", 1); // 榛樿瑙ｉ攣绗竴鍏�
    skill1 = UserDefault::getInstance()->getIntegerForKey("Skill1Level", 0);
    skill2 = UserDefault::getInstance()->getIntegerForKey("Skill2Level", 0);

    // 娣诲姞鑳屾櫙
    auto background = Sprite::create("start_background.jpg");
    background->setPosition(Director::getInstance()->getVisibleSize() / 2); // 璁剧疆鑳屾櫙浣嶇疆涓哄睆骞曚腑蹇�
    background->setScale(1.5f);
    this->addChild(background, 0); // 灏嗚儗鏅坊鍔犲埌鍦烘櫙涓紝灞傜骇涓�0

    // 鍗囩骇鐣岄潰
    auto upgradeButton = MenuItemImage::create("upgrade.png", "upgrade.png", CC_CALLBACK_1(LevelScene::enterUpgradeScene, this));
    upgradeButton->setPosition(Vec2(1100, 100));

    // 杩斿洖閿�
    auto backButton = ui::Button::create("exit.png", "exit.png");
    backButton->setPosition(Vec2(100, 600));
    backButton->addClickEventListener(CC_CALLBACK_1(LevelScene::goBack, this));
    this->addChild(backButton);

    //娓呯┖鍘嗗彶璁板綍閿�
    auto clearButton = ui::Button::create("clear.png", "clear.png");
    clearButton->setPosition(Vec2(100, 100));
    clearButton->setScale(0.5f);
    clearButton->addClickEventListener(CC_CALLBACK_1(LevelScene::clear, this));
    this->addChild(clearButton);

    // 閫夋嫨鍏冲崱鎸夐挳
    auto level1Button = MenuItemImage::create("game1.png", "game1.png", CC_CALLBACK_1(LevelScene::selectLevel1, this));
    auto level2Button = MenuItemImage::create("game2.png", "game2.png", CC_CALLBACK_1(LevelScene::selectLevel2, this));
    auto level3Button = MenuItemImage::create("game3.png", "game3.png", CC_CALLBACK_1(LevelScene::selectLevel3, this));
    level1Button->setPosition(Vec2(200, 400));
    level2Button->setPosition(Vec2(600, 400));
    level3Button->setPosition(Vec2(1000, 400));
    


    m_level1Button = level1Button;
    m_level2Button = level2Button;
    m_level3Button = level3Button;


    // 璁剧疆鍒濆鐨勫浘鐗�
    m_level1Button->setNormalImage(Sprite::create("game1.png"));
    m_level2Button->setNormalImage(Sprite::create("game2.png"));
    m_level3Button->setNormalImage(Sprite::create("game3.png"));

    // 鏄剧ず money 鏁伴噺鐨� Label
    auto background1 = Sprite::create("qian.png"); // 浣跨敤鎸囧畾鐨勫浘鐗囨枃浠跺垱寤� Sprite 瀵硅薄浣滀负鑳屾櫙
    background1->setPosition(Vec2(100, 700)); 

    this->addChild(background1);

    m_moneyLabel = Label::createWithTTF("      0", "fonts/Marker Felt.ttf", 32);
    m_moneyLabel->setPosition(Vec2(100, 700));
    this->addChild(m_moneyLabel);

    auto menu = Menu::create(level1Button, level2Button, level3Button, upgradeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    // 鍒濆鍖栨寜閽姸鎬�
    m_unlockedLevel1 = true;
    m_unlockedLevel2 = (m_unlockLevel >= 2);
    m_unlockedLevel3 = (m_unlockLevel >= 3);

    updateButtonState(); // 鏇存柊鎸夐挳鐘舵��

    return true;
}

// 杩斿洖鏍囬鐣岄潰
void LevelScene::goBack(Ref* pSender)
{
    // 淇濆瓨鏁版嵁
    UserDefault::getInstance()->setIntegerForKey("Money", money);
    UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", m_unlockLevel);
    UserDefault::getInstance()->setIntegerForKey("Skill1Level", skill1);
    UserDefault::getInstance()->setIntegerForKey("Skill2Level", skill2);
    UserDefault::getInstance()->flush(); // 纭繚鏁版嵁琚啓鍏�

    Director::getInstance()->popScene();
}


void LevelScene::selectLevel1(Ref* sender)
{


    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

    m_gameScene = Scene1::createScene(1, this); // 浼犻�掑叧鍗＄紪鍙�

    Director::getInstance()->pushScene(m_gameScene);
}

void LevelScene::selectLevel2(Ref* sender)
{
    if (m_unlockLevel >= 2) // 濡傛灉绗簩鍏冲凡瑙ｉ攣
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene2::createScene(2, this); // 浼犻�掑叧鍗＄紪鍙峰拰 LevelScene 鍦烘櫙鐨勬寚閽�

        Director::getInstance()->pushScene(m_gameScene);
    }
}

void LevelScene::selectLevel3(Ref* sender)
{
    if (m_unlockedLevel3) // 濡傛灉绗笁鍏冲凡瑙ｉ攣
    {

        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        m_gameScene = Scene3::createScene(3, this); // 浼犻�掑叧鍗＄紪鍙峰拰 LevelScene 鍦烘櫙鐨勬寚閽�
        Director::getInstance()->pushScene(m_gameScene);
    }
}


void LevelScene::updateButtonState()
{
    m_moneyLabel->setString("       " + std::to_string(money));
    if (m_unlockedLevel2)
    {
        m_level2Button->setNormalImage(Sprite::create("game2.png")); // 瑙ｉ攣鍚庣殑鍥剧墖
    }
    else
    {
        m_level2Button->setNormalImage(Sprite::create("game2_locked.png")); // 鏈В閿佺殑鍥剧墖

    }

    if (m_unlockedLevel3)
    {
        m_level3Button->setNormalImage(Sprite::create("game3.png")); // 瑙ｉ攣鍚庣殑鍥剧墖
    }
    else
    {
        m_level3Button->setNormalImage(Sprite::create("game3_locked.png")); // 鏈В閿佺殑鍥剧墖
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

    updateButtonState(); // 鏇存柊鎸夐挳鐘舵�佸拰鍥剧墖
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

// 鎶�鑳�1鍗囩骇

void LevelScene::upgradeItem1() {
    skill1 += 1;
}

// 鎶�鑳�2鍗囩骇

void LevelScene::upgradeItem2() {
    skill2 += 1;
}

// 杩斿洖鎶�鑳�1绛夌骇

int LevelScene::getItem1Level() {
    return skill1;
}

// 杩斿洖鎶�鑳�2绛夌骇
int LevelScene::getItem2Level() {
    return skill2;
}

//娓呯┖鍘嗗彶璁板綍
void LevelScene::clear(Ref* sender) {
    // 娓呯┖淇濆瓨鐨勬暟鎹�
    UserDefault::getInstance()->setIntegerForKey("Money", 0);
    UserDefault::getInstance()->setIntegerForKey("UnlockedLevel", 1); // 閲嶇疆涓洪粯璁よВ閿佺涓�鍏�
    UserDefault::getInstance()->setIntegerForKey("Skill1Level", 0);
    UserDefault::getInstance()->setIntegerForKey("Skill2Level", 0);
    UserDefault::getInstance()->flush(); 

    // 鏇存柊褰撳墠鍦烘櫙鐨勭姸鎬�
    money = 0;
    m_unlockLevel = 1;
    skill1 = 0;
    skill2 = 0;

    updateButtonState(); // 鏇存柊鎸夐挳鐘舵��
    Director::getInstance()->popScene();
}

