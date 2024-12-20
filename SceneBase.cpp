#include "SceneBase.h"
#include "SimpleAudioEngine.h"
#include "Obstacle.h"
#include "Monster.h"
#include "Tower.h"
#include "TowerPosition.h"
#include "ui/CocosGUI.h"
#include "levelScene.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC; 

Sprite* plusIcon;

SceneBase* SceneBase::createScene(int level, LevelScene* levelScene)
{
    SceneBase* scene = new SceneBase();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

// 打印有用的错误消息，而不是在文件不存在时段错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void SceneBase::update(float delta)
{
    time += delta;
    if (!carrot->isAlive()) {
        this->setButton(false);
    }
    if (monsterFlag)
    {
        int num = 0;
        // 遍历场景中的所有节点
        for (auto child : this->getChildren())
        {
            // 判断该节点是否为 Monster 类型
            auto monster = dynamic_cast<Monster*>(child);
            if (monster != nullptr)
            {
                num++;
            }
        }
        if (num == 0 && carrot->isAlive())
        {
            this->setButton(true);
        }
    }
}


/*
* 显示层数：
* 0层：地图背景
* 1层：萝卜、障碍物、炮塔的底座、钱
* 2层：放置的炮塔、子弹
* 3层：炮塔位置的加号、加号上面的可选炮塔按钮
* 4层：进度条
* 5层：结束界面
* 6层：结束界面上面的按钮
*/

void SceneBase::initScene(std::string& mapName) {
    auto map = TMXTiledMap::create(mapName);
    this->addChild(map, 0);     // 添加到场景中，显示在第0层

    setPauseButton();           //放置暂停按钮
    setMenuButton();

    // 获取萝卜对象层
    TMXObjectGroup* carrotObjects = map->getObjectGroup("Carrot");

    // 获取萝卜对象的位置信息
    const auto& firstCarrotObject = carrotObjects->getObjects().at(0);
    float xC = firstCarrotObject.asValueMap().at("x").asFloat() + 60;
    float yC = firstCarrotObject.asValueMap().at("y").asFloat() + 70;

    // 创建萝卜并放置在地图上的位置

    carrot->setCarrotPosition(Vec2(xC, yC)); //设置萝卜位置
    carrot->putCarrot(10 + 5 * m_levelScene->getItem2Level());          //真初始化，10:萝卜血量
    this->addChild(carrot, 1);      // 添加到场景中，显示在第1层，确保在地图上方显示

    TMXObjectGroup* towerPositions = map->getObjectGroup("TowerPosition");
    // 处理位置对象
    ValueVector towerPositionsVector = towerPositions->getObjects();

    for (const auto& towerPosition : towerPositionsVector)
    {
        // 获取炮塔位置对象的位置信息
        float xP = towerPosition.asValueMap().at("x").asFloat() + 50;
        float yP = towerPosition.asValueMap().at("y").asFloat() + 50;

        // 创建炮塔位置并放置在地图上
        Vec2 position = Vec2(xP, yP);
        TowerPosition* towerPos = TowerPosition::create();
        towerPos->setPosition(position);
        towerPos->setVisible(false);        // 初始化时设置为隐藏状态
        this->addChild(towerPos, 1);        // 添加到场景中，显示在第3层，确保在地图上方显示

    }

    // 添加障碍物
    TMXObjectGroup* GrassObjects = map->getObjectGroup("Grass"); // 获取障碍物对象层
    ValueVector obstaclePositionsVector = GrassObjects->getObjects();

    for (const auto& obstacle : obstaclePositionsVector) {
        float xO = obstacle.asValueMap().at("x").asFloat();
        float yO = obstacle.asValueMap().at("y").asFloat();

        // 创建障碍物并放置在地图上
        Grass* Grass = Grass::create();
        Grass->setPosition(Vec2(xO + 50, yO + 50));
        this->addChild(Grass, 0); // 添加到场景中
    }

    TMXObjectGroup* StoneObjects = map->getObjectGroup("Stone");
    ValueVector stonePositionsVector = StoneObjects->getObjects();

    for (const auto& stone : stonePositionsVector) {
        float xS = stone.asValueMap().at("x").asFloat();
        float yS = stone.asValueMap().at("y").asFloat();

        // 创建石头障碍物并放置在地图上
        Stone* Stone = Stone::create();
        Stone->setPosition(Vec2(xS + 100, yS + 50));
        this->addChild(Stone, 0); // 添加到场景中
    }

    // 处理宝箱对象
    TMXObjectGroup* TreasureObjects = map->getObjectGroup("Treasure");
    ValueVector treasurePositionsVector = TreasureObjects->getObjects();

    for (const auto& treasure : treasurePositionsVector) {
        float xT = treasure.asValueMap().at("x").asFloat();
        float yT = treasure.asValueMap().at("y").asFloat();

        //创建宝箱并放置在地图上
        Treasure* Treasure = Treasure::create();
        Treasure->setPosition(Vec2(xT + 100, yT + 100));
        this->addChild(Treasure, 0); // 添加到场景中
    }


    // 添加鼠标事件监听器，用于处理塔位置对象的显示和隐藏
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto children = this->getChildren();
        for (Node* child : children) {
            TowerPosition* towerPos = dynamic_cast<TowerPosition*>(child);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerSelect.mp3"); //播放点击音效
            // 移除所有的升级按钮
            if (towerPos && towerPos->towerofThisPosition)
            {
                towerPos->towerofThisPosition->removeChildByName("But");
                towerPos->towerofThisPosition->removeChildByName("But");
                if (towerPos->towerofThisPosition->bottom) {
                    towerPos->towerofThisPosition->bottom->removeAllChildren();
                }
            }
                 if (towerPos) {
                if (towerPos->getBoundingBox().containsPoint(touch->getLocation())) {
                    // 检查是否可以在此位置放置塔
                    bool canBuild = true;
                    for (Node* child : this->getChildren()) {
                        Obstacle* obstacle = dynamic_cast<Obstacle*>(child);
                        if (obstacle && obstacle->getBoundingBox().intersectsRect(towerPos->getBoundingBox())) {
                            canBuild = false; // 如果存在重叠，不能建造
                            break;
                        }
                    }

                    // 当前位置没有障碍物，可以显示建造界面
                    if (canBuild) {
                        // 当前位置有塔
                        if (towerPos->towerofThisPosition)
                        {
                            towerPos->setVisible(false);

                            towerPos->towerofThisPosition->clicked(moneyScene);

                        }
                    }
                // 没有塔，显示建造界面
                else {
                    towerPos->setVisible(true);
                    // 创建按钮
                    Vec2 positionButtonBottle = Vec2(-100, 120);
                    Vec2 positionButtonFire = Vec2(-20, 120);
                    Vec2 positionButtonStar = Vec2(60, 120);
                    Vec2 positionButtonSunflower = Vec2(140, 120);
                    Vec2 positionButtonShit = Vec2(220, 120);
                    Vec2 positionCheck = towerPos->getPosition();
                    if (positionCheck.x == 50)      //如果位置紧贴左边缘，对建立的按钮相对坐标进行处理，使按钮显示在右侧
                    {
                        positionButtonBottle = Vec2(120, -100);
                        positionButtonFire = Vec2(120, -20);
                        positionButtonStar = Vec2(120, 60);
                        positionButtonSunflower = Vec2(120, 140);
                        positionButtonShit = Vec2(120, 220);
                    }
                    // 创建按钮
                    auto buttonBottle = cocos2d::ui::Button::create("BottleButton.png", "BottleButton.png", "BottleButtonUn.png");
                    buttonBottle->setPosition(positionButtonBottle);
                    buttonBottle->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonBottle, 0, "BottleButton");
                    // 设置点击状态
                    if (this->moneyScene >= 100) {
                        buttonBottle->setEnabled(true);
                    }
                    else {
                        buttonBottle->setEnabled(false);
                    }
                    // 创建按钮
                    auto buttonFire = cocos2d::ui::Button::create("FireBottleButton.png", "FireBottleButton.png", "FireBottleButtonUn.png");
                    buttonFire->setPosition(positionButtonFire);
                    buttonFire->addClickEventListener(CC_CALLBACK_1(SceneBase::createFire, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonFire, 0, "FireButton");
                    // 设置点击状态
                    if (this->moneyScene >= 160) {
                        buttonFire->setEnabled(true);
                    }
                    else {
                        buttonFire->setEnabled(false);
                    }
                    // 创建按钮                  
                    auto buttonStar = cocos2d::ui::Button::create("StarButton.png", "StarButton.png", "StarButtonUn.png");
                    buttonStar->setPosition(positionButtonStar);
                    buttonStar->addClickEventListener(CC_CALLBACK_1(SceneBase::createStar, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonStar, 0, "StarButton");
                    // 设置点击状态
                    if (this->moneyScene >= 200) {
                        buttonStar->setEnabled(true);
                    }
                    else {
                        // 提示用户无法在障碍物上建造
                        CCLOG("无法在障碍物上建造!");
                    }
                }
                else {
                    towerPos->setVisible(false);

                    // 查找和移除所有的建造按钮
                    cocos2d::ui::Button* spriteBottle = static_cast<cocos2d::ui::Button*>(this->getChildByName("BottleButton"));
                    if (spriteBottle) {
                        // 子节点存在，可以进行移除操作
                        this->removeChildByName("BottleButton");
                    }
                    else {
                        buttonSunflower->setEnabled(false);
                    }

                    // 创建按钮                  
                    auto buttonShit = cocos2d::ui::Button::create("ShitButton.png", "ShitButton.png", "ShitButtonUn.png");
                    buttonShit->setPosition(positionButtonShit);
                    buttonShit->addClickEventListener(CC_CALLBACK_1(SceneBase::createShit, this));  // 添加按钮点击回调函数
                    towerPos->addChild(buttonShit, 0, "ShitButton");
                    // 设置点击状态
                    if (this->moneyScene >= 120) {
                        buttonShit->setEnabled(true);
                    }
                    else {
                        buttonShit->setEnabled(false);
                    }
                }
            }
            // 没有被点击的方块
            else if (towerPos)
            {
                towerPos->setVisible(false);

                    cocos2d::ui::Button* spriteStar = static_cast<cocos2d::ui::Button*>(this->getChildByName("StarButton"));
                    if (spriteStar) {
                        // 子节点存在，可以进行移除操作
                        this->removeChildByName("StarButton");
                    }

                cocos2d::ui::Button* spriteFire = static_cast<cocos2d::ui::Button*>(this->getChildByName("FireButton"));
                if (spriteBottle) {
                    // 子节点存在，可以进行移除操作
                    this->removeChildByName("FireButton");
                }

                    cocos2d::ui::Button* spriteSunflower = static_cast<cocos2d::ui::Button*>(this->getChildByName("SunflowerButton"));
                    if (spriteSunflower) {
                        // 子节点存在，可以进行移除操作
                        this->removeChildByName("SunflowerButton");
                    }

                }

                cocos2d::ui::Button* spriteShit = static_cast<cocos2d::ui::Button*>(this->getChildByName("ShitButton"));
                if (spriteShit) {
                    // 子节点存在，可以进行移除操作
                    this->removeChildByName("ShitButton");
                }
            }
        }
        return true;
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SceneBase::menuCloseCallback(Ref* pSender)
{
    //这个函数会停止游戏循环，并释放所有的资源。
    Director::getInstance()->end();

    //如果希望在iOS中返回原生界面而不是退出应用程序，可以注释掉这个函数，并调用下面的代码，
    //触发一个名为“game_scene_close_event”的自定义事件，由RootViewController.mm文件中的代码处理。

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void SceneBase::createBottle(cocos2d::Ref* sender)
{
    // 在当前位置创建炮塔
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerBulid.mp3"); //播放炮塔建立音效
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = BottleTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());// 设置底座位置
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;//
                tower->thisTowerPositionIS = thisTowerPosition;//

            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);
            tower->bottom = bottom;//
            this->updateMoney(-100);
        }
    }
}
void SceneBase::createFire(Ref* sender)
{
    // 在当前位置创建炮塔
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerBulid.mp3"); //播放炮塔建立音效
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = FireTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());// 设置底座位置
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;//
                tower->thisTowerPositionIS = thisTowerPosition;//

            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);
            tower->bottom = bottom;//
            this->updateMoney(-100);
        }
    }
}

void SceneBase::createStar(cocos2d::Ref* sender)
{
    // 在当前位置创建星星炮塔
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerBulid.mp3"); //播放炮塔建立音效
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = StarTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
                tower->thisTowerPositionIS = thisTowerPosition;
            }
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);

            this->updateMoney(-200);
        }
    }
}

void SceneBase::createSunflower(cocos2d::Ref* sender)
{
    // 在当前位置创建太阳花炮塔
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerBulid.mp3"); //播放炮塔建立音效
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = SunflowerTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
                tower->thisTowerPositionIS = thisTowerPosition;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);
            tower->bottom = bottom;
            this->updateMoney(-120);
        }
    }
}

void SceneBase::createShit(Ref* sender)
{
    // 在当前位置创建屎炮塔
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("TowerBulid.mp3"); //播放炮塔建立音效
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = ShitTower_1::create();  // 创建炮塔对象
        if (moneyScene >= tower->getConsumption())
        {
            tower->setPosition(button->getParent()->getPosition());  // 设置炮塔位置
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
                tower->thisTowerPositionIS = thisTowerPosition;
            }
            this->addChild(tower, 2);  // 将炮塔添加到场景中
            button->getParent()->setVisible(false);

            this->updateMoney(-120);
        }
    }
}


// on "init" you need to initialize your instance
bool SceneBase::init(int level, LevelScene* levelScene)
{
    // 调用了父类Scene的init()函数进行初始化，如果初始化失败，则返回false
    if (!Scene::init())
    {
        return false;
    }
    

    m_levelScene = levelScene;
    // 创建定时器，定时更新怪物状态
    scheduleUpdate();
    return true;
}


void SceneBase::setButton(bool flag)
{
    if (flag)
    {
        auto closeWin = Sprite::create("WinPicture.png");
        closeWin->setPosition(Vec2(650, 400));
        this->addChild(closeWin, 5, "WinBackground");

        auto continueGame = MenuItemImage::create(
            "ContinueGame.png",
            "ContinueGame.png",
            CC_CALLBACK_0(SceneBase::onGameWin, this));
        auto menuContinue = Menu::create(continueGame, nullptr);
        menuContinue->setPosition(Vec2(650, 265));    // 设置按钮位置
        this->addChild(menuContinue, 6, "ContinueGame");
        //Director::getInstance()->pause();           // 暂停游戏
    }
    else
    {
        auto closeFail = Sprite::create("FailPicture.png");
        closeFail->setPosition(Vec2(650, 420));
        this->addChild(closeFail, 5, "FailBackground");

        auto goBack = MenuItemImage::create(
            "GoBack.png",
            "GoBack.png",
            CC_CALLBACK_0(SceneBase::onGameFail, this));
        auto menuBack = Menu::create(goBack, nullptr);
        menuBack->setPosition(Vec2(650, 265));      // 设置按钮位置
        this->addChild(menuBack, 6, "GoBack");
        Director::getInstance()->pause();           // 暂停游戏
    }
}

void SceneBase::setPauseButton()
{
    // 创建按钮                 
    auto pauseGame = cocos2d::ui::Button::create("Pause2.png", "Pause2.png");
    pauseGame->setPosition(Vec2(1100, 750));    // 设置按钮位置
    pauseGame->addClickEventListener(CC_CALLBACK_0(SceneBase::pauseOperate, this));
    this->addChild(pauseGame, 4, "Pause");

    auto continueGame = cocos2d::ui::Button::create("Pause1.png", "Pause1.png");
    continueGame->setPosition(Vec2(1100, 750));    // 设置按钮位置
    continueGame->addClickEventListener(CC_CALLBACK_0(SceneBase::continueOperate, this));
    continueGame->setVisible(false);
    this->addChild(continueGame, 5, "Continue");

    //Director::getInstance()->pause();           // 暂停游戏
}

void SceneBase::pauseOperate()
{
    auto Continue = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("Continue"));
    Continue->setVisible(true);
    Director::getInstance()->pause();           // 暂停游戏
}

void SceneBase::continueOperate()
{
    Director::getInstance()->resume();          // 恢复游戏
    auto Continue = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("Continue"));
    Continue->setVisible(false);
}

void SceneBase::setMenuButton()
{
    // 创建按钮
    auto menuButton = cocos2d::ui::Button::create("touming-hd.png", "touming-hd.png");
    menuButton->setPosition(Vec2(1200, 750));    // 设置按钮位置
    menuButton->addClickEventListener(CC_CALLBACK_0(SceneBase::onGameMenu, this));
    this->addChild(menuButton, 4, "Menu");

    auto GameMenu = Sprite::create("GameMenu.png");
    GameMenu->setPosition(Vec2(650, 400));
    this->addChild(GameMenu, 5, "GameMenu");

    auto continueGame = cocos2d::ui::Button::create("ContinueGame.png", "ContinueGame.png");
    continueGame->setPosition(Vec2(650, 365));    // 设置按钮位置
    continueGame->addClickEventListener(CC_CALLBACK_0(SceneBase::continueGame, this));
    this->addChild(continueGame, 6, "ContinueGame");

    auto goBack = cocos2d::ui::Button::create("GoBack.png", "GoBack.png");
    goBack->setPosition(Vec2(650, 265));    // 设置按钮位置
    goBack->addClickEventListener(CC_CALLBACK_0(SceneBase::goBack, this));
    this->addChild(goBack, 6, "GoBack");

    GameMenu->setVisible(false);
    continueGame->setVisible(false);
    goBack->setVisible(false);
}

void SceneBase::onGameMenu()
{
    auto GameMenu = dynamic_cast<cocos2d::Sprite*>(this->getChildByName("GameMenu"));
    auto continueGame = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("ContinueGame"));
    auto menuGoBack = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("GoBack"));
    GameMenu->setVisible(true);
    continueGame->setVisible(true);
    menuGoBack->setVisible(true);
    Director::getInstance()->pause();             // 暂停游戏
}

void SceneBase::continueGame()
{
    Director::getInstance()->resume();            // 恢复游戏
    auto GameMenu = dynamic_cast<cocos2d::Sprite*>(this->getChildByName("GameMenu"));
    auto continueGame = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("ContinueGame"));
    auto menuGoBack = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("GoBack"));
    GameMenu->setVisible(false);
    continueGame->setVisible(false);
    menuGoBack->setVisible(false);
}

void SceneBase::goBack()
{
    // 游戏完成时调用此函数
    if (m_levelScene)
    {
        //停下音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
        Director::getInstance()->resume();          // 恢复游戏
        Director::getInstance()->popScene();        // 返回到上一个场景
    }
}

void SceneBase::onGameWin()
{
    // 游戏完成时调用此函数
    if (m_levelScene)
    {
        //停下音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();

        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
        int nextLevel = m_level + 1;
        m_levelScene->consumeMoney(-100);
        m_levelScene->unlockLevel(nextLevel);       // 解锁下一关
        Director::getInstance()->popScene();        // 返回到上一个场景
    }
}

void SceneBase::onGameFail()
{
    // 游戏完成时调用此函数
    if (m_levelScene)
    {
        //停下音乐
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
        Director::getInstance()->resume();          // 恢复游戏
        Director::getInstance()->popScene();        // 返回到上一个场景
    }
}

void SceneBase::addMoney(int money)
{
    this->moneyScene += money;
}

void SceneBase::updateMoney(int money)
{
    moneyScene += money;
    this->removeChild(m_lable);
    std::string text = std::to_string(moneyScene); // 将数字转换为字符串
    auto lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    lable->setPosition(Vec2(150, 750));
    this->m_lable = lable;
    this->addChild(m_lable, 1);
}
