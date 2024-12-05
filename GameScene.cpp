//#include "SceneMain.h"
//#include "GameScene.h"
//#include "LevelScene.h"
//#include "audio/include/SimpleAudioEngine.h"
//USING_NS_CC;
//
//
//GameScene* GameScene::create(int level, LevelScene* levelScene)
//{
//    GameScene* scene = new GameScene();
//    if (scene && scene->init(level, levelScene))
//    {
//        scene->autorelease();
//        return scene;
//    }
//    else
//    {
//        delete scene;
//        return nullptr;
//    }
//}
//
//bool GameScene::init(int level, LevelScene* levelScene)
//{
//    if (!Scene::init())
//    {
//        return false;
//    }
//    
//    // ������������ֲ�
//    auto mask = Sprite::create("mubu.jpg");
//    mask->setPosition(Vec2(0, 320)); // ���ó�ʼλ������Ļ��
//    this->addChild(mask, 1);
//
//    // �ƶ����ֲ�
//    auto moveAction = MoveBy::create(1.0f, Vec2(1960, 0)); // �ƶ���ָ��λ��
//    auto removeAction = RemoveSelf::create();
//    auto sequence = Sequence::create(moveAction, removeAction, nullptr);
//    mask->runAction(sequence);
//
//    m_level = level;
//    m_levelScene = levelScene; // ����ؿ�ѡ�񳡾���ָ��
//    int ml = levelScene->m_unlockLevel;
//
//    // ��������ݹؿ���ż��ض�Ӧ����Ϸ��Դ���߼�
//
//    // ... ������ʼ������ ...
//
//    // ���һ����ť�����ڱ�ʾ��Ϸ���
//    auto completeButton = MenuItemImage::create(
//        "button_normal.png",
//        "button_selected.png",
//        CC_CALLBACK_0(GameScene::onGameComplete, this));
//    auto menu = Menu::create(completeButton, nullptr);
//    levelScene->money = levelScene->money + 50;
//    menu->setPosition(Vec2(650, 420)); // ���ð�ťλ��
//    addChild(menu);
//
//    return true;
//}
//
//void GameScene::onGameComplete()
//{
//    // ��Ϸ���ʱ���ô˺���
//    if (m_levelScene)
//    {
//        //����
//        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("main.mp3");
//        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
//
//        int nextLevel = m_level + 1;
//        m_levelScene->updateScene(nextLevel, 1); // ������һ��
//        Director::getInstance()->popScene();  // ���ص���һ������
//    }
//}